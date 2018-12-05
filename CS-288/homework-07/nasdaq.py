import sys
import mysql.connector


def insert(cursor, values):
    query = "INSERT INTO nasdaq(timestamp,exchange,symbol,company,volume,price,percentChange) VALUES (%s,%s,%s,%s,%s,%s,%s)"
    cursor.execute(query, values)
    # cursor.execute(query, ("0385514239", "Origin", 2995))


# def update(cursor, values):
#     query = "UPDATE book SET price=%s WHERE isbn=%s"
#     cursor.execute(query, (29.95, "0385514239"))


if len(sys.argv) < 2:
    print("missing args")
    exit(1)


try:
    cnx = mysql.connector.connect(
        host="localhost", user=sys.argv[1], password=sys.argv[2], database="demo"
    )
    cursor = cnx.cursor()

    insert(cursor)
    cnx.commit()

    update(cursor)
    cnx.commit()

    cursor.close()
except mysql.connector.Error as err:
    print(err)
finally:
    try:
        cnx
    except NameError:
        pass
    else:
        cnx.close()
