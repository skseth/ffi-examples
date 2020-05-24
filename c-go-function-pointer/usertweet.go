package usertweet


// UserTweet handle for operating on twitter api
type UserTweet struct {
	id	string
}

// New authenticates to twitter api and return a new handle
func New() *UserTweet {
	return &UserTweet{id: "anid"}
}

// GetLastTweet returns string of the last tweet from a user
func (u *UserTweet) GetLastTweet(user string) (string, error) {
	return "No tweets!", nil
}
