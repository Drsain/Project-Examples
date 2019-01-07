"""
	The library class is where most of the code is implemented. It holds the arrays of data, and functions to checkout, add and print books
"""

class library:
	def __init__(self, schoolName, studentLimitBooks, studentLimitDays, teacherLimitBooks, teacherLimitDays, costOverdue):

		self.name = schoolName ##setting the library name
		self.library = {} ##creating the library dictionary. A dictionary is accesses by a key and not the position of the data in the array. This makes is really easy to look up a book based on its ID
		self.users = [] ##Creating the array of users
		self.slb = studentLimitBooks ##setting the max number of books a student can check out
		self.tlb = teacherLimitBooks ##setting the max number of books a teacher can check out
		self.sld = studentLimitDays ##setting the max number of days a student can check out a book
		self.tld = teacherLimitDays ##setting the max number of days a student can check out a book
		self.cost = costOverdue ##setting the cost of an overdue book

	"""
	A function that adds a book to the library array
	"""

	def addBook(self, IDnumber, bookName, bookAuthor):

		newBook = book(IDnumber,bookName,bookAuthor) ##creating the new book in memory
		self.library[IDnumber] = newBook ##adding that book to the array
		print "The book %s has been added, and its new ID is %i" % (bookName, IDnumber) ##a print statement saying that this action has been successful
		inp = raw_input('Type enter to continue')
##A function that adds a user to the user array
	def addUser(self, name, type):

		valid = False 
		while valid == False: ##a loop for error checking
			if type == 1: ## figuring out if the user is a student
				valid = True
				newUser = student(name, self.sld, self.slb) ##creating the new user in memory
				self.users.append(newUser) ##adding the user to the array
				print "%s has been added as a new student" % (name) ##print statement saying the action was successful
				inp = raw_input('Type enter to continue')
			elif type == 2: ## figuring out if the user is a teacher
				valid = True
				newUser = teacher(name, self.tld, self.tld) ##creating the new user in memory
				self.users.append(newUser) ##adding the user to the array
				print "%s has been added as a new teacher" % (name) ##print statement saying the action was successful
				inp = raw_input('Type enter to continue')
			else: ##a invalid output, now attempting to make the user give the program a valid output
				newInput = raw_input("Invalid output please enter a new type: student or teacher: ")
				if newInput.lower() == "student":
					type = 1
				elif newInput.lower() == "teacher":
					type = 2
				else:
					type = 3


##A function that checks out a book
	def checkout(self, ID, user, dates=None):

		if len(user.books) < user.Lbooks: ##figuring out if the user has the max number of books already checked out
			if self.library[ID].owner == None: ##figuring out if the book is already checked out
				self.library[ID].owner = user ##setting the new user
				if dates != None:
					self.library[ID].time = dates ##setting the time that the book was checked out
				else:
					self.library[ID].time = date.today() ##setting the time that the book was checked out
				user.books.append(self.library[ID]) ##adding the book to the user array for furthur checking
				print "The user %s, is now the owner of the book %s" % (user,self.library[ID]) ##print statement to show the code was successful
				inp = raw_input('Type enter to continue')
			else:
				print "Error this book has already been checked out" ##attempting to error correct (book was already checked out)
				inp = raw_input('Type enter to continue')
		else:
			print "Error the user %s already has the maxium about of books checked out" % (user.name) ##attempting to error correct (had max books)
			print "Please return one of these books to check out the book %s: " % (self.library[ID].name)
			for i in user.books:
				print i
			inp = raw_input('Type enter to continue')

	##a function that returns a book to the library
	def returnBook(self, ID, user):

		if self.library[ID].owner != user: ##checking to make sure the book is actually the users to return
			print "You are trying to return a book that the user %s didn't check out" % (user)
			inp = raw_input('Type enter to continue')
		else: ##attempting to return
			self.overdue(self.library[ID].time,user.Ldays) ##checking if overdue
			user.books.remove(self.library[ID]) ##removing the book from the user array
			self.library[ID].owner=None ##removing the owner, making it be returned to the library
			print "The book has been returned" ##print statement saying the action was successful
			inp = raw_input('Type enter to continue')


	##A function that checks the dates a book was checked out and todays date to figure out if it is overdue

	def overdue(self, bookDate, limit, ID):

		today=date.today() ##finding todays date
		dateDifference = today-bookDate ##figuring out difference
		diff = limit - dateDifference.days ##figuring out how long it is overdue
		if diff < 0: ##it is overdue
			price = float(abs(diff)*(self.cost)) ##figuring out price
			print "The book with ID %i is overdue by %i owe the library %s dollars" % (ID,diff,'{0:.2f}'.format(price)) ##print statement to show the book is overdue
		else: ##book not overdue
			print "The book with ID %i is not overdue and has %i days left" % (ID,diff) ##print statement showing the book is not overdue

	##A report that prints all of the book 
	def reportNorm(self):
		print "This report will show each book followed by its current owner\nand if checked out then the time remaining till the return deadline" ##print to help user understand what is going on
		for key in self.library.keys(): ##looping through books in library
			if self.library[key].owner == None: ##figuring out owner (library)
				owner = "library"
			else:##figuring out owner (user)
				owner = self.library[key].owner.name
			today=date.today() ##figuring out todays date
			bookDate = self.library[key].time 
			dateDifference = today-bookDate ##figuring out time left/overdue
			if self.library[key].owner != None:  ##figuring out if needed to print time left
				diff = self.library[key].owner.Ldays - dateDifference.days
				diff = str(diff)
			else:
				diff = "0"
			print type(diff) 
			print "ID: %i         Book: %s        Current owner: %s        Time left (0 if in library): %s" % (key,self.library[key].name,owner,diff) ##printing out the lnfromation

	##A report that prints information about books that are checked out
	def reportOver(self):
		print "This report will show more details about checked out books"
		for key in self.library.keys(): ##looping through the books
			if self.library[key].owner == None: ##going over those without a owner
				continue
			else:
				bookDate = self.library[key].time
				limit = self.library[key].owner.Ldays
				self.overdue(bookDate,limit,key) ##checking if overdue

	##long function that works as the interface for users. It transverses through the menu and lets the user choose different options
	##This uses if statements and try/except statements to catch any errors or incorrect inputs
	def interface(self):
		print "\n\n\n\n\n\n\n"
		print "Welcome to the %s library interface" % (self.name)
		cont = True
		while cont == True:
			try:
				print "\n\n\n\n"
				print "In menu"
				print "Type a number to change menus\n1 to view/edit/add users\n2 to view/add books\n3 to change limits\n4 to checkout and return books\n5 to view report"
				try:
					inp = input('')
				except:
					print "Please enter a number"
					inp = raw_input('Type enter to continue')
				if inp == 1:
					print "\n\n\n\n"
					print "Type a number to do an action\n1 to view all users\n2 to view details on one user\n3 to edit a user\n4 to add a new user\n5 to go back"
					try:
						inp = input('')
					except:
						print "Please enter a number"
					if inp == 1:
						print "\n\n\n\n"
						for i in self.users:
							print i
						inp = raw_input('Type enter to continue')
					elif inp == 2:
						print "Please enter the name of the user to see: "
						inp = raw_input('')
						u = None
						for i in self.users:
							if i.name == inp:
								u=i
						if u == None:
							print "This user does not exist"
							inp = raw_input('Type enter to continue')
						else:
							print u
							print "The user has checked out these books:"
							print u.books
							inp = raw_input('Type enter to continue')
					elif inp == 3:
						print "Please enter the name of the user to edit: "
						inp = raw_input('')
						u = None
						for i in self.users:
							if i.name == inp:
								u=i
						if u == None:
							print "This user does not exist"
							inp = raw_input('Type enter to continue')
						else:
							print "Please enter a new name: "
							inp = raw_input('')
							u.name = inp
							print "The users name has been changed to %s" % (u.name)
							inp = raw_input('Type enter to continue')
					elif inp == 4:
						print "Please enter a name seperated by the type:\nThe input Bob,student will add a new student with the name Bob"
						inp = raw_input('')
						inp = inp.split(",")
						if inp[1] == "student":
							Type = 1
						elif inp[1] == "teacher":
							Type = 2
						else:
							Type = inp[1]
						self.addUser(inp[0],Type)
						inp = raw_input('Type enter to continue')
					elif inp == 5:
						continue
					else:
						print "Error invalid input"
						inp = raw_input('Type enter to continue')
				elif inp == 2:
					print "\n\n\n\n"
					print "Type a number to do an action\n1 to view all books\n2 to view details on one book\n3 to add a new book\n4 to go back"
					try:
						inp = input('')
					except:
						print "Please enter a number"
						inp = raw_input('Type enter to continue')
					if inp == 1:
						print "\n\n\n\n"
						for i in self.library:
							print i
						inp = raw_input('Type enter to continue')
					elif inp == 2:
						print "\n\n\n\n"
						print "Please enter the ID of the book to see: "
						u = None
						try:
							inp = input('')
							for key in self.library.keys():
								if key == inp:
									u = key
						except:
							print "Please enter a number"
							inp = raw_input('Type enter to continue')
						if u != None:
							print self.library[u]
							daysDiff = self.library[u].time - date.today()
							print "Owned by %s for %s days" % (self.library[u].owner,daysDiff.days)
							inp = raw_input('Type enter to continue')
					elif inp == 3:
						print "\n\n\n\n"
						print "Please enter the name and author seperated by a comma: "
						inp = raw_input('')
						inp = inp.split(",")
						newID = len(self.library)+1
						self.addBook(newID,inp[0],inp[1])
					elif inp == 4:
						continue
					else:
						print "Error invalid input"
						inp = raw_input('Type enter to continue')
				elif inp == 3:
					print "\n\n\n\n"
					print "Please enter a number to do an action\n1 to change the number of books a student can have\n2 to change the number of books a teacher can have\n3 to change the number of days a student can have a book\n4 to change the number of days a teacher can have a book"
					try:
						inp = input('')
					except:
						print "Please enter a number"
						inp = raw_input('Type enter to continue')
					if inp == 1:
						print "Please enter a new number of books a student can check out: "
						try:
							inp = input('')
							self.slb = inp
							for i in users:
								if i.t == 1:
									i.changeLimitBooks(inp)
							inp = raw_input('Type enter to continue')
						except:
							print "Please enter a number"
							inp = raw_input('Type enter to continue')
					elif inp == 2:
						print "Please enter a new number of books a teacher can check out: "
						try:
							inp = input('')
							self.slb = inp
							for i in users:
								if i.t == 2:
									i.changeLimitBooks(inp)
							inp = raw_input('Type enter to continue')
						except:
							print "Please enter a number"
							inp = raw_input('Type enter to continue')
					elif inp == 3:
						print "Please enter a new number of days a student can have a book: "
						try:
							inp = input('')
							self.slb = inp
							for i in users:
								if i.t == 1:
									i.changeLimitDays(inp)
							inp = raw_input('Type enter to continue')
						except:
							print "Please enter a number"
							inp = raw_input('Type enter to continue')
					elif inp == 4:
						print "Please enter a new number of days a teacher can have a book: "
						try:
							inp = input('')
							self.slb = inp
							for i in users:
								if i.t == 2:
									i.changeLimitDays(inp)
							inp = raw_input('Type enter to continue')
						except:
							print "Please enter a number"
							inp = raw_input('Type enter to continue')
					else:
						print "Error invalid input"
						inp = raw_input('Type enter to continue')
				elif inp == 4:
					print "\n\n\n\n"
					print "Please enter a number to do an action\n1 to checkout a book\n2 to return a book"
					try:
						inp = input('')
					except:
						print "Please enter a number"
						inp = raw_input('Type enter to continue')
					if inp == 1:
						print "Please enter the ID of the book being checked out"
						try:
							inp = input('')
						except:
							print "Please enter a number"
							inp = raw_input('Type enter to continue')
							inp = None
						ID = inp
						print "Please enter the name of the user that wants to check out the book"
						inp = raw_input('')
						for i in self.users:
							if i.name == inp:
								user = i
						self.checkout(ID,user)
					elif inp == 2:
						print "Please enter the ID of the book being returned"
						try:
							inp = input('')
						except:
							print "Please enter a number"
							inp = raw_input('Type enter to continue')
							inp = None
						ID = inp
						print "Please enter the name of the user that wants to return the book"
						inp = raw_input('')
						for i in self.users:
							if i.name == inp:
								user = inp
						self.returnBook(ID,user)
					else:
						print "Error invalid input"
						inp = raw_input('Type enter to continue')
				elif inp == 5:
					print "\n\n\n\n"
					self.reportNorm()
					inp = raw_input('Type enter to continue')
					self.reportOver()
					inp = raw_input('Type enter to continue')
				elif inp == 99:
					cont = False
			except:
				print "Please enter a correct input"
				inp = raw_input('Type enter to continue')


	##A class of books that allows for easier data allocation
class book:
	def __init__(self, IDnumber=0, bookName="", bookAuthor="", owner=None, time=0):
		self.ID = IDnumber ##setting the ID number
		self.name = bookName ##setting the name
		self.author = bookAuthor ##setting the author
		self.owner = owner ##setting the owner
		if time == 0:
			self.time = date.today() ##setting the new date if a date isnt given
		else:
			self.time = time ##setting the date if a date is given
	def __repr__(self): ## what is printed when a book is called in a print statement
		return "%s,%s" % (self.name,self.author)



	##a class of user made specifically for the students
class student:
	def __init__(self, studentName, studentLimitDays, studentLimitBooks):
		self.name = studentName ##setting the name
		self.Ldays = studentLimitDays ##setting the max number of days a student can check out a book
		self.Lbooks = studentLimitBooks ##setting the max number of books a student can check out
		self.books = [] ##an array of books that a student has checked out
		self.t = 1 ##the type (only helpful for the coder)

	##a function to change the max number of days

	def changeLimitDays(self, changeLimitDays):
		self.Ldays = changeLimitDays

	##a function to change the max number of books
	def changeLimitBooks(self, changeLimitBooks):
		self.Lbooks = changeLimitBooks
	def __repr__(self):
		return "Student,%s" % (self.name)## what is printed when a book is called in a print statement


	##a function that changes the name of the user
	def changeName(self, newName):
		print "The student's name was: %s. \nIt is now %s." % (self.name,newName)
		self.name = newName

	##a class of user made specifically for the teachers
class teacher:
	def __init__(self, teacherName, teacherLimitDays, teacherLimitBooks):
		self.name = teacherName ##setting the name
		self.Ldays = teacherLimitDays ##setting the max number of days a teacher can check out a book
		self.Lbooks = teacherLimitBooks ##setting the max number of books a teacher can check out
		self.books = [] ##an array of books that a teacher has checked out
		self.t = 2 ##the type (only helpful for the coder)
	##a function to change the max number of days
	def changeLimitDays(self, changeLimitDays):
		self.Ldays = changeLimitDays
	##a function to change the max number of days
	def changeLimitBooks(self, changeLimitBooks):
		self.Lbooks = changeLimitBooks

	def __repr__(self): ## what is printed when a teacher is called in a print statement
		return "Teacher,%s" % (self.name)

	##a function that changes the name of the user
	def changeName(self, newName):
		print "The teacher's name was: %s. \nIt is now %s." % (self.name,newName)
		self.name = newName

def main():

	##Testing code (can be uncommented and used if necessary, is just used by me to make sure that the functions worked before using the user interface):

	"""test1 = library("test",5,15,6,20,.1)
	test1.addBook(1,"My Book","Dylan Sain")
	print test1.library
	print test1.library[1]
	print test1.library[1].ID
	print test1.library[1].author
	print test1.library[1].owner
	print test1.library[1].time
	print "\n"

	for i in range(2,22):
		newBookName = "Book" + str(i)
		newAuthor = "Author" + str(i)
		test1.addBook(i,newBookName,newAuthor)
	print test1.library
	print "\n"

	test1.addUser("User1",1)
	print test1.users[0]
	print test1.users[0].name
	print "\n"

	test1.addUser("User2",4)
	print test1.users[1]
	print test1.users[1].name
	print "\n"

	print test1.users
	print "\n"

	test1.checkout(1,test1.users[0])
	test1.checkout(1,test1.users[1])
	print "\n"

	test1.returnBook(1,test1.users[0])
	test1.returnBook(2,test1.users[0])
	print "\n"

	test1.checkout(1,test1.users[0])
	test1.checkout(2,test1.users[0])
	print test1.users[0].books
	test1.returnBook(1,test1.users[0])
	print test1.users[0].books
	test1.returnBook(2,test1.users[0])
	print "\n"

	today = date.today()
	newDate = date(2015,today.month,today.day)
	print newDate
	test1.checkout(1,test1.users[0],newDate)
	test1.overdue(test1.users[0].books[0].time,test1.sld)
	print "\n"""


	##set up code:
	ok = False
	name = raw_input('Please enter the name of the library: ')
	while ok == False:
		limits = raw_input('Please enter the max number of books a student and teacher can checkout.\nMust be seperated by a comma (can be changed later).\n')
		limits = limits.split(",")
		try:
			for i in range(len(limits)):
				limits[i] = int(limits[i])
			ok = True
		except:
			print "Error please enter the information like this: 1,1. This will set the max student days to 1 and the max teacher days to 1"
	ok = False
	while ok == False:
		days = raw_input('Please enter the max number of days a student and teacher can checkout a book.\nMust be seperated by a comma (can be changed later).\n')
		days = days.split(",")
		try:
			for i in range(len(days)):
				days[i] = int(days[i])
			ok = True
		except:
			print "Error please enter the information like this: 1,1. This will set the max student books to 1 and the max teacher books to 1"
	ok = False
	while ok == False:
		try:
			over = input('Please enter overdue cost per day (can be changed later):\n')
			ok = True
		except:
			print "Please enter a number"
	l = library(name,limits[0],days[0],limits[1],days[1],over)
	l.interface()





if __name__ == "__main__":
	global time
	import time
	global date
	from datetime import date
	main()