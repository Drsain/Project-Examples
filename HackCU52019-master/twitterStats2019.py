# Import the tweepy library
import tweepy
# Variables that contains the user credentials to access Twitter API 
ACCESS_TOKEN = 'access token'
ACCESS_SECRET = 'access secret'
CONSUMER_KEY = 'consumer key'
CONSUMER_SECRET = 'consumer secret'


def userInfo(user_name, api):
	try:
		user = api.get_user(user_name)
	except: 
		print("Error retrieving user. Please try again")
		return

	

	#print('Gathering Data...')
	


	print('\n')
	print('Analyzing: @' + user.screen_name)
	#date account was created
	print(user.name + "'s account created on: " + str(user.created_at))
	#users bio
	if(user.description):
		print(user.name + "'s Bio: " + user.description)
	#checks if user is verified
	if(user.verified):
		print(user.name + ' is Verified')
	else:
		print(user.name + ' is NOT Verified')
	#checks if users tweets are protected
	if(user.protected):
		print(user.name + "'s tweeets are protected")
	else:
		print(user.name + "'s tweets are NOT protected")
	#if the user specifies a location, display it
	if(user.location):
		print(user.name + "'s location: " + user.location)
	#follower, tweet counts
	print('Following: ' + str(user.friends_count))
	print('Followers: ' + str(user.followers_count))
		#display url if applicable
	if(user.url):
		print(user.name + "'s website: " + user.url)
	print('\n')







def analyizeUserTweets(user_name, api):
	#find users most retweeted/liked/replied tweet
	try:
		user = api.get_user(user_name)
	except: 
		print("Error retrieving user. Please try again")
		return

	pages = [x for x in range(10)]
	original_tweets = 0
	retweets = 0
	check_if_first = True
	max_retweet = None
	max_like = None
	print("Analyzing tweets...")
	print('\n')
	#find popular tweets
	list_of_tweets = []
	for i in pages:
		list_of_tweets.extend(api.user_timeline(screen_name = user_name, count = 1000, page = i))
		if(user.statuses_count == 0):
			print("User has no tweets")
			return

	for j in list_of_tweets:
		if(hasattr(j, 'retweeted_status')):
				retweets+=1
		if(check_if_first):
			if (not hasattr(j, 'retweeted_status')):
				max_retweet = j
				max_like = j
				check_if_first = False
		else:
			if(j.retweet_count > max_retweet.retweet_count and not hasattr(j, 'retweeted_status')):
				max_retweet = j

			if(j.favorite_count > max_like.favorite_count and not hasattr(j, 'retweeted_status')):
				max_like = j
	#calculate number of tweets/retweets
	total_tweets = user.statuses_count + retweets
	print('Number of Total Tweets: ' + str(total_tweets))
	print("Number of Original Tweets: " + str(user.statuses_count))
	print("Number of Retweets: " + str(retweets))


	print('\n')

	print(user.name + "'s most recent tweet:")
	most_recent = api.user_timeline(screen_name = user_name, count = 1)
	if(hasattr(most_recent[0], 'retweeted_status')):
		most_recent[0] = most_recent[0].retweeted_status
	print(most_recent[0].text)
	print(most_recent[0].source)
	print(str(most_recent[0].retweet_count) + " Retweets 	" + str(most_recent[0].favorite_count) + " Likes")
	print(most_recent[0].created_at)
	print('\n')

	print(user.name + "'s most retweeted tweet:")
	print(max_retweet.text)
	print(max_retweet.source)
	print(str(max_retweet.retweet_count) + " Retweets 	" + str(max_retweet.favorite_count) + " Likes")
	print(max_retweet.created_at)
	print('\n')

	print(user.name + "'s most liked tweet:")
	print(max_like.text)
	print(max_like.source)
	print(str(max_like.retweet_count) + " Retweets 	 " + str(max_like.favorite_count) + " Likes")
	print(max_like.created_at)
	print('\n')



def followStats(user_name, api):
	try:
		user = api.get_user(user_name)
	except: 
		print("Error retrieving user. Please try again")
		return

	print("Analyzing Followers... \n")
	print("Follower to Following ratio: " + str('%.4f'%(user.followers_count / user.friends_count)) + '\n')
	#find most popular follow
	if(user.followers_count < 1000):
		followers = []
		popular_follower = None
		first_pop = True
		page_count = 0
		for currentUser in tweepy.Cursor(api.followers, id = user_name, count = 200).pages():
			page_count +=1
			followers.extend(currentUser)
		for i in followers:
			if(first_pop):
				popular_follower = i
				first_pop = False 
			else:
				if(i.followers_count > popular_follower.followers_count):
					popular_follower = i

		print(user.name + "'s most popular follow:")
		print("@" + popular_follower.screen_name)
		print(popular_follower.name)
		if(popular_follower.verified):
			print(popular_follower.name + ' is Verified')
		else:
			print(popular_follower.name + ' is NOT Verified')
		print("Followers: " + str(popular_follower.followers_count))
	else:
		print("@" + user.screen_name + "'s follower count too large to find most popular follow")
	print('\n')
	#find most popular user they are following
	if(user.friends_count < 1000):
			friends = []
			popular_friend = None
			first_pop = True
			page_count = 0
			for currentUser in tweepy.Cursor(api.friends, id = user_name, count = 200).pages():
				page_count +=1
				friends.extend(currentUser)
			for i in friends:
				if(first_pop):
					popular_friend = i
					first_pop = False 
				else:
					if(i.followers_count > popular_friend.followers_count):
						popular_friend = i

			print("Most popular user " + user.name + " is following: ")
			print("@" + popular_friend.screen_name)
			print(popular_friend.name)
			if(popular_friend.verified):
				print(popular_friend.name + ' is Verified')
			else:
				print(popular_friend.name + ' is NOT Verified')
			print("Followers: " + str(popular_friend.followers_count))
	else:
			print("@" + user.screen_name + "'s follower count too large to find the most popular user they are following")






def main():

	# Setup tweepy to authenticate with Twitter credentials:

	auth = tweepy.OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)
	auth.set_access_token(ACCESS_TOKEN, ACCESS_SECRET)

	# Create the api to connect to twitter with your creadentials
	api = tweepy.API(auth, wait_on_rate_limit=True, wait_on_rate_limit_notify=True, compression=True)
	#---------------------------------------------------------------------------------------------------------------------
	# wait_on_rate_limit= True;  will make the api to automatically wait for rate limits to replenish
	# wait_on_rate_limit_notify= Ture;  will make the api  to print a notification when Tweepyis waiting for rate limits to replenish
	#---------------------------------------------------------------------------------------------------------------------
	user_name = 'jacob_felknor'

	userInfo(user_name, api)
	analyizeUserTweets(user_name, api)
	followStats(user_name, api)




if __name__ == "__main__":
	main()
