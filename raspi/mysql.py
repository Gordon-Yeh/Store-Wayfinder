"""
Connect to and query database from Raspberry Pi 
"""
import mysql.connector

host = 'cpen391.cpyc6b2epdjj.us-west-1.rds.amazonaws.com'
user = 'root'
password = 'bairiyishanjin'
database = 'cpen391'

def db_init():
    db = mysql.connector.Connect(
        host = host,
        user = user,
        passwd = password,
        database = database
    )
    cursor = db.cursor()
    retutn cursor

#search the db to get the 
def search_name(cursor, keyword):
    cursor.execute("SELECT x, y FROM Items WHERE name="+ keyword + ";")
    result = cursor.fetchall()
    return result

def search_cat(cursor, keyword):
    cursor.execute("SELECT name FROM Items WHERE category=" + keyword + ";")
    result = cursor.fetchall()
    return result

def main():
    cursor = db_init()
    location = search_name(cursor, "test")
    print(location)
