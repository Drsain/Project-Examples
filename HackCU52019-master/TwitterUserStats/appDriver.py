from flask import Flask, render_template, redirect, url_for, request, send_from_directory
try:
    import json
except ImportError:
    import simplejson as json
import tweepy

# Variables that contains the user credentials to access Twitter API 
ACCESS_TOKEN = '3067050784-dHA28dy0Q5dRQ6gq0FbtP1RSOIiUTUaqbGorU3e'
ACCESS_SECRET = 'prXOwddr07Pz5kcuwZYTOxKGWRkbjylaqsr022EvhkHXu'
CONSUMER_KEY = 'mjjwlnKgURc4IkQ4bZ55GlVJp'
CONSUMER_SECRET = '2eDxNQ1AjRc7lEe2XbgvW1DJ6BZjaoojiStIdEGYhtqmcoF6hL'


a = Flask(__name__)

@a.route('/', methods = ['GET', 'POST'])
def home():

	auth = tweepy.OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)
	auth.set_access_token(ACCESS_TOKEN, ACCESS_SECRET)

	api = tweepy.API(auth, wait_on_rate_limit=True, wait_on_rate_limit_notify=True, compression=True)


	twitterArray = []
	if request.method == 'POST':
		reqform = request.form['userName']
		user = api.get_user(reqform)

		twitterArray.append('@' + user.screen_name + ' Name')
		twitterArray.append(user.name)


		twitterArray.append(user.name + "'s account created on")
		twitterArray.append(str(user.created_at))


		twitterArray.append(user.name + "'s Bio")
		if(user.description):
			twitterArray.append(user.description)
		else:
			twitterArray.append("No User Description")


		twitterArray.append('Verified')
		if(user.verified):
			twitterArray.append('Yes')
		else:
			twitterArray.append('No')


		twitterArray.append('Protected')
		if(user.protected):
			twitterArray.append('Yes')
		else:
			twitterArray.append('No')


		twitterArray.append('Location')
		if(user.location):
			twitterArray.append(user.location)
		else:
			twitterArray.append('No location specified')


		twitterArray.append('Following')
		twitterArray.append(str(user.friends_count))


		twitterArray.append('Followers')
		twitterArray.append(str(user.followers_count))


		twitterArray.append('Url listed')
		if(user.url):
			twitterArray.append(user.url)
		else:
			twitterArray.append('No website specified')




		pages = [x for x in range(10)]
		original_tweets = 0
		retweets = 0
		check_if_first = True
		max_retweet = None
		max_like = None
		list_of_tweets = []
		for i in pages:
			list_of_tweets.extend(api.user_timeline(screen_name = reqform, count = 1000, page = i))
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
		total_tweets = user.statuses_count + retweets
		most_recent = api.user_timeline(screen_name = reqform, count = 1)




		twitterArray.append('Total Tweets')
		twitterArray.append(str(total_tweets))


		twitterArray.append('Original Tweets')
		twitterArray.append(str(user.statuses_count))


		twitterArray.append('Retweets')
		twitterArray.append(str(retweets))


		twitterArray.append('Most Recent Tweet')
		if(hasattr(most_recent[0], 'retweeted_status')):
			twitterArray.append(most_recent[0].text)
			twitterArray.append("RTs:" + str(most_recent[0].retweet_count) + "  Likes:" + str(most_recent[0].retweeted_status.favorite_count))
			twitterArray.append(most_recent[0].source)

		else:
			twitterArray.append(most_recent[0].text)
			twitterArray.append("RTs:" + str(most_recent[0].retweet_count) + "  Likes:" + str(most_recent[0].favorite_count))
			twitterArray.append(most_recent[0].source)

		twitterArray.append('Most Retweeted Tweet')
		twitterArray.append(max_retweet.text)
		twitterArray.append("RTs:" + str(max_retweet.retweet_count) + "  Likes:" + str(max_retweet.favorite_count))
		twitterArray.append(max_retweet.source)


		twitterArray.append('Most Liked Tweet')
		twitterArray.append(max_like.text)
		twitterArray.append("RTs:" + str(max_like.retweet_count) + "  Likes:" + str(max_like.favorite_count))
		twitterArray.append(max_like.source)















		twitterArray.append('Follower to Following ratio')
		if(user.friends_count == 0):
			twitterArray.append("Error: ratio undefined")
		else:
			var = float(user.followers_count) / user.friends_count
			twitterArray.append(str('%.4f'%(var)))


		if(user.followers_count < 1000):
			followers = []
			popular_follower = None
			first_pop = True
			page_count = 0
			for currentUser in tweepy.Cursor(api.followers, id = reqform, count = 200).pages():
				page_count +=1
				followers.extend(currentUser)
			for i in followers:
				if(first_pop):
					popular_follower = i
					first_pop = False 
				else:
					if(i.followers_count > popular_follower.followers_count):
						popular_follower = i


			twitterArray.append('Most Popular Follower')
			twitterArray.append('@' + popular_follower.screen_name)
			twitterArray.append(popular_follower.name)
			twitterArray.append('Verified')
			if(popular_follower.verified):
				twitterArray.append('Yes')
			else:
				twitterArray.append('No')
			twitterArray.append('Followers')
			twitterArray.append(str(popular_follower.followers_count))
		else:
			twitterArray.append('Follower Count is too High')
			twitterArray.append("NA")
			twitterArray.append("NA")
			twitterArray.append("NA")
			twitterArray.append("NA")
			twitterArray.append("NA")
			twitterArray.append("NA")


		if(user.friends_count < 1000):
			friends = []
			popular_friend = None
			first_pop = True
			page_count = 0
			for currentUser in tweepy.Cursor(api.friends, id = reqform, count = 200).pages():
				page_count +=1
				friends.extend(currentUser)
			for i in friends:
				if(first_pop):
					popular_friend = i
					first_pop = False 
				else:
					if(i.followers_count > popular_friend.followers_count):
						popular_friend = i


			twitterArray.append('Most Popular User @' + user.screen_name + ' follows')
			twitterArray.append('@' + popular_friend.screen_name)
			twitterArray.append(popular_friend.name)
			twitterArray.append('Verified')
			if(popular_friend.verified):
				twitterArray.append('Yes')
			else:
				twitterArray.append('No')
			twitterArray.append('Followers')
			twitterArray.append(str(popular_friend.followers_count))
		else:
			twitterArray.append('Following Count is too High')
			twitterArray.append("NA")
			twitterArray.append("NA")
			twitterArray.append("NA")
			twitterArray.append("NA")
			twitterArray.append("NA")
			twitterArray.append("NA")






	return render_template('home.html', twitterArray = twitterArray)

if __name__ == '__main__':
	a.run(debug=True)