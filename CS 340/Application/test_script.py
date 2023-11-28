'''
Name          : Animal Shelter Database Test Script
Author        : Keith Breazeale
Date          : 28-November 2023
Class         : CS-340
Version       : 2.0
Purpose       : To test the CRUD Operations of the Grazioso Salvare Animal Shelter Database
'''

from animal_shelter import AnimalShelter
shelter = AnimalShelter("aacuser","aacuser")

data = {"1": 3,
        "age_upon_outcome" : "4 years",
        "animal_id" : "27-Mar-2023_test"
        "animal_type" :"Dog",
        "breed" : "Bluetick Coonhound",
        "color" : "Black and White",
        "date_of_birth" : "2019-01-01",
        "datetime" : "2019-01-01 00:00:00",
        "monthyear" : "2019-01-01T00:00:00",
        "name" : "Courage",
        "outcome_subtype" : "",
        "outcome_type" : "Adoption",
        "sex_upon_outcome" : "Female",
        "location_lat" : 35.651150,
        "location_long" : -78.746020,
        "age_upon_outcome_in_weeks" : 220}

#Create Test
shelter.create(data):
    print("Animal added successfully!")


#Read Test
result = shelter.read(data)
print(result)

#Update Test
result = shelter.update({"name" : "Courage"}, {"sex_upon_outcome" : "Spayed Female"})
print(result)

#Confirm update
result = shelter.read({"name" : "Courage"})
print(result)

#Delete Test
result = shelter.delete({"name" : "Courage"})
print(result)

#Confirm deletion
result = shelter.read({"name" : "Courage"})
print(result)
