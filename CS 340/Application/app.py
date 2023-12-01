'''
Name          : Grazioso Salvare Animal Finder Dashboard
Author        : Keith Breazeale
Date          : 20-Noveber 2023
Class         : CS-340
Version       : 2.0
Purpose       : To display a functioning dashboard based off of the Animal Shelter Database
'''

from jupyter_plotly_dash import JupyterDash

import dash
import dash_leaflet as dl
#import from dash import dcc - deprecated
from dash import dcc
#import from dash import html - deprecated
from dash import html
import plotly.express as px
import dash_table as dt
from dash.dependencies import Input, Output, State

import os
import base64
import numpy as np
import pandas as pd
from pymongo import MongoClient
from bson.json_util import dumps

from animal_shelter import AnimalShelter

############################################
# Authentication / Data Manipulation / Model
############################################

username = "aacuser"
password = "aacuser"
shelter = AnimalShelter(username, password)


# class read method must support return of cursor object 
df = pd.DataFrame.from_records(shelter.read_all({}))



#########################
# Dashboard Layout / View
#########################
# Minor enhancement: Updated Dashboard title.
# Minor enhancement: Updated Logo from 685 x 683px to 302 x 319px

app = dash.Dash('Grazioso Salvare Animal Finder Dashboard')
image_filename = 'GSLogo.png' # replace with your own image
encoded_image = base64.b64encode(open(image_filename, 'rb').read())

app.layout = html.Div([
    html.Center(html.B(html.H1('Grazioso Salvare Animal Finder Dashboard'))),
    html.Center(
        html.Img(src='data:image/png;base64,{}'.format(encoded_image.decode()))),
    # Unique identifier 
    html.Center(html.H1('Developed by Keith Breazeale 7-November-2023')),
    html.Hr(),
    #Enhancement Comment - Dropdown Filter Setup
    html.Div([
        dcc.Dropdown(
            id='dropdown',
            options=[
                {'label': 'Water Rescue', 'value': 'WR'},
                {'label': 'Mountain or Wilderness Rescue', 'value': 'MR'},
                {'label': 'Disaster or Individual Tracking Rescue', 'value': 'DR'},
                {'label': 'Reset', 'value': 'reset'}
            ],
            value='Reset'
        ),
        html.Div(id='dd-output-container')
    ]),
    html.Hr(),
    #Enhancement Comment - Interactive Table Settings
    dt.DataTable(
        id='datatable-id',
        columns=[
            {"name": i, "id": i, "deletable": False, "selectable": True} for i in df.columns
        ],
        data=df.to_dict('records'),
        editable=False,
        filter_action="native",
        sort_action="native",
        sort_mode="multi",
        column_selectable=False,
        row_selectable=False,
        row_deletable=False,
        selected_columns=[],
        selected_rows=[0],
        page_action="native",
        page_current=0,
        page_size=10,
    ),

    html.Br(),
    html.Hr(),
    
    #This sets up the dashboard so that your chart and your geolocation chart are side-by-side
    html.Div(className='row',
             style={'display': 'flex'},
             children=[
                 dcc.Graph(
                     id="pie-chart",
                     className='col s12 m6',
                 ),
                 html.Div(
                     id='map-id',
                     className='col s12 m6',
                 )
             ])
])

#############################################
# Interaction Between Components / Controller
#############################################

@app.callback(
    [Output('datatable-id', 'data'),
     Output('datatable-id','columns')],
    [dash.dependencies.Input('dropdown', 'value')])
#Enhancement Comment - Water Rescue Filter
def update_output(value):
    if (value =='WR'):
        df = pd.DataFrame(list(shelter.read_all(
            { 
            "breed": {
                "$in": [
                    "Labrador Retriever Mix",
                    "Chesapeake Bay Retriever",
                    "Newfoundland"
                ]
            },
            "sex_upon_outcome": "Intact Female",
            "age_upon_outcome_in_weeks": {
                "$gte": 26.0
            },
            "$and": [
                {
                    "age_upon_outcome_in_weeks": {
                        "$lte": 156.0
                    }
                }
            ]
        }
        )))
    #Enhancement Comment - Mountain or Wilderness Rescue Filter    
    elif (value == 'MR'):
        df = pd.DataFrame(list(shelter.read_all(
            { 
            "breed": {
                "$in": [
                    "German Shepherd",
                    "Alaskan Malamute",
                    "Old English Sheepdog",
                    "Siberian Husky",
                    "Rottweiler"
                ]
            },
            "sex_upon_outcome": "Intact Male",
            "age_upon_outcome_in_weeks": {
                "$gte": 26.0
            },
            "$and": [
                {
                    "age_upon_outcome_in_weeks": {
                        "$lte": 156.0
                    }
                }
            ]
        }
        )))
    #Enhancement Comment - Disaster or Individual Tracking Rescue Filter    
    elif (value == 'DR'):
        df = pd.DataFrame(list(shelter.read_all(
            { 
            "breed": {
                "$in": [
                    "Doberman Pinscher",
                    "German Shepherd",
                    "Golden Retriever",
                    "Bloodhound",
                    "Rottweiler"
                ]
            },
            "sex_upon_outcome": "Intact Male",
            "age_upon_outcome_in_weeks": {
                "$gte": 20.0
            },
            "$and": [
                {
                    "age_upon_outcome_in_weeks": {
                        "$lte": 300.0
                    }
                }
            ]
        }
        )))
    else:
        df = pd.DataFrame.from_records(shelter.read_all({}))
        
    columns=[{"name": i, "id": i, "deletable": False, "selectable": True} for i in df.columns]
    data=df.to_dict('records')
    
    return (data,columns)
    


# Enhancement: This callback will highlight a column or row on the data table when the user, at first, selects it on the currently visible page
@app.callback(
    Output('datatable-id', 'style_data_conditional'),
    [Input('datatable-id', 'selected_columns'),
     Input('datatable-id', "derived_viewport_selected_rows"),
     Input('datatable-id', 'active_cell')]
)
def update_styles(selected_columns, selected_rows, active_cell):
    if active_cell is not None:
        style = [{
                    'if': { 'row_index': active_cell['row'] },
                    'background_color':'#a5d6a7'
                }]
    else:
        style = [{
                    'if': { 'row_index': i },
                    'background_color':'#a5d6a7'
                } for i in selected_rows]
        
    return (style +
                [{
                    'if': { 'column_id': i },
                    'background_color': '#80deea'
                } for i in selected_columns]
            )
# This callback adds a pie chart that displays breed percentage from the interactive data table
@app.callback(
    Output("pie-chart", "figure"),
    [Input("datatable-id", "data")]
)
def generate_chart(data):
    dff = pd.DataFrame.from_dict(data)
    fig = px.pie(
        dff,
        names='breed',
        #Minor Enhancement - Improved title of the chart for a better user experience.
        title='Animal Rescue Breeds by Percentage',
    )
    return fig

# This callback adds a geolocation chart to plot an animal to the map based on the selection from the data table.
# Enhancement - Fixed issue with selection not being plotted after the filter was generated.
@app.callback(
    Output('map-id', "children"),
    [Input('datatable-id', "derived_viewport_data"),
     Input('datatable-id', "derived_viewport_selected_rows"),
     Input('datatable-id', "active_cell")]
)
def update_map(viewData, selected_rows, active_cell):

    dff = pd.DataFrame.from_dict(viewData)

    # define marker position of one selected row
    if active_cell is not None:
        row = active_cell['row']
    else:
        row = selected_rows[0]
        
    lat = dff.loc[row,'location_lat']
    long = dff.loc[row,'location_long']
    name = dff.loc[row,'name']
    breed = dff.loc[row,'breed']
    animal = dff.loc[row, 'animal_type']
    age = dff.loc[row, 'age_upon_outcome']
    
    return [
        dl.Map(
            style={'width': '1000px', 'height': '500px'},
            center=[lat,long], zoom=10,
            children=[
                dl.TileLayer(id="base-layer-id"),
                # Marker with tool tip and popup
                dl.Marker(
                    position=[lat,long],
                    children=[
                        dl.Tooltip("({:.3f}, {:.3f})".format(lat,long)),
                        dl.Popup([
                            html.H2(name),
                            html.P([
                                html.Strong("{} | Age: {}".format(animal,age)),
                                html.Br(),
                                breed])
                        ])
                    ]
                )
            ]
        )
    ]

if __name__ == '__main__':
   app.run_server(debug=True)