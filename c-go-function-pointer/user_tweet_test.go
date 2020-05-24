package usertweet

import (
	"fmt"
	"testing"
)

func TestGetLastTweet(t *testing.T) {
	u := New()
	tweet, err := u.GetLastTweet("VersitySoftware")
	if err != nil {
		t.Errorf("%v", err)
	}
	fmt.Println(tweet)
}

