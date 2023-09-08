import mysql.connector
val1,val2,val3,val4,val5=21,13,53,1,34
mydb = mysql.connector.connect(
#  host="",
  user="root",
  password="nguyenlu123",
  database="mydatabase"
)

mycursor = mydb.cursor()

mycursor.execute("SELECT Word from value_in WHERE Word='Hi'")
myresult=mycursor.fetchall()
for x in myresult:
  print(x) 