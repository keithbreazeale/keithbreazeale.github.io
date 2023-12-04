'''
Name          : Animal Shelter Database Connector
Author        : Keith Breazeale
Date          : 20-Noveber 2023
Class         : CS-340
Version       : 2.0
Purpose       : This Python script aims to supply a MongoDB database for the Grazioso Salvare Animal Shelter Database, 
                enabling the Dashboard's functionality. After establishing a successful connection, testers can utilize 
                the CRUD methods using the test_script.py. The Read All Method specifically allows the dashboard to 
                retrieve data from the database.
'''

from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    
#Connect to the database. If MongoDB is on a different port, be sure to update it line 17 to use the correct port number, currently set to 27017.
    def __init__(self,username,password):
        self.client = MongoClient('mongodb://%s:%s@localhost:27017/?authMechanism=DEFAULT&authSource=AAC'% ('aacuser','aacuser'))
        self.database = self.client['AAC']

#Create Method
    def create(self, data):
        if data is not None:
            self.database.animals.insert(data)  # data should be dictionary
            return True
        else:
            raise Exception("Nothing to save, because data parameter is empty!")
            return False
            
#Read Method
    def read(self, data):
        if data is not None:
            return self.database.animals.find_one(data)
        else:
            print("Nothing to read, because data parameter is empty!")
            return False

#Read All Method        
    def read_all(self, data):
        cursor = self.database.animals.find(data, {'_id':False} ) #return cursor pointer to list of results
        return cursor
        
#Update Method
    def update(self, data, updateData):
        if data is not None:
            result = self.database.animals.update_many(data, {"$set" : updateData})
        else:
            return "{}"
        print ("Record Updated!")
        return result.raw_result
            
#Delete Method
    def delete(self, data):
        if data is not None:
            result = self.database.animals.delete_many(data)
        else:
            return "{}"
        print("Record Deleted")
        return result.raw_result
