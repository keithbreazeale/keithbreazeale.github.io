# 5-1 Project One
# Keith Breazeale
# 27-March-2023

from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    
    def __init__(self,username,password):
    # init to connect to mongodb without authentication
        #self.client = MongoClient('mongodb://localhost:43981')
        
    # init connect to mongodb with authentication
        self.client = MongoClient('mongodb://%s:%s@localhost:43981/?authMechanism=DEFAULT&authSource=AAC'% ('aacuser','aacuser'))
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