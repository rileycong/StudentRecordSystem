import pymysql

def getConnection(): 
    connection = pymysql.connect(host='127.0.0.1',
                                 user='root',
                                 password='1234',                             
                                 db='srs_python')
    return connection