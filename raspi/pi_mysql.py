"""python script for pulling data from aws database
    Use different functions to handle different user requests incliuding
    - auto-complete for search
    - get info of a searched item
    - 
    Author: Skylar
    Date: Feb 19, 2019
"""

#"python -m pip install mysql-connector" to install the db connector
import sys
sys.path.insert(0, "/usr/local/lib/python2.7/dist-packages/mysql")
import connector

host = 'cpen391.cpyc6b2epdjj.us-west-1.rds.amazonaws.com'
user = 'root'
password = 'bairiyishanjin'
database = 'cpen391'

class DB(object):
    def __init__(self):
        self.conn = connector.Connect(
            host = host,
            user = user,
            passwd = password,
            database = database
        )
        self.cursor = self.conn.cursor()

    def search_name(self, keyword):
        self.cursor.execute("SELECT x FROM Items WHERE name='"+ keyword + "';")
        x = self.cursor.fetchall()
        self.cursor.execute('SELECT y FROM Items WHERE name="'+ keyword + '";')
        y = self.cursor.fetchall()
        return x, y

# def db_init():
#     db = connector.Connect(
#         host = host,
#         user = user,
#         passwd = password,
#         database = database
#     )
#     cursor = db.cursor()
#     return cursor

#search the db to get the 
def search_name(cursor, keyword):
    cursor.execute("SELECT x FROM Items WHERE name="+ keyword + ";")
    x = cursor.fetchall()
    cursor.execute("SELECT y FROM Items WHERE name="+ keyword + ";")
    y = cursor.fetchall()
    return x, y

def search_cat(cursor, keyword):
    cursor.execute("SELECT name FROM Items WHERE category=" + keyword + ";")
    result = cursor.fetchall()
    return result

# def mainSQL():
#     cursor = db_init()
#     location = search_name(cursor, "test")
#     print(location)

