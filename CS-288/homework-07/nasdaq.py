import mysql.connector
import sys

cnx = mysql.connector.connect(
    user=sys.argv[1], password=sys.argv[2], host="localhost", database="demo"
)

print(cnx)
