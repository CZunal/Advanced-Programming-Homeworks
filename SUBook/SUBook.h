#ifndef SUBOOK_H
#define SUBOOK_H


//Prepared by Can Zunal 29453
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class User;
class Post;
class Comment;


class User
{
private:
	string name;
	int num_comments;
	vector<Post*> posts;
	
public:

	User(string username) //A constructor that takes the user’s name as a parameter
	{
		name = username;
		num_comments = 0;
	} //Constructor with username parameter

	~User();
	Post& createPost(string content); //creates a new Post object with the given contentand adds it to the user's posts list. The function returns a reference to the created post.
	vector<Post*> getPosts(); //return a vector of pointers to the posts of the user.
	int getNumComments(); //returns the number of comments made by the user.If the user doesn’t have any comments yet, the function returns 0.
	string getName(); // get the name of the user.

	void incrementCommentNum();	//Extra function to increment comments
	void DecrementCommentNum();	//Extra function to decrement comments



};

class Post
{
private:
	string contentOfPost;
	User* userOfPost;
	vector<Comment*> comments;
public:
	
	Post(string txt, User* username)  
	{
		userOfPost = username;
		contentOfPost = txt;
	}

	~Post(); //A destructor that will delete all the comments on this post
	void addComment(string content, User* commenter); //adds a comment by “commenter” with the content given
	vector<Comment*> getComments(); //: get a vector of pointers at the comments on this post
	User& getUser();
	string getContent();
};


class Comment
{
private:
	User* userOfComment;
	string contentOfComment;
	Post* postOfComment;
public:

	Comment(User* username, string txt, Post* post)
	{
		userOfComment = username;
		contentOfComment = txt; 
		postOfComment = post;
	}
	~Comment(); //Destructor that decrement number of comment of the user by 1
	User& getUser(); //returns the user who made the comment
	string getContent();  //returns the text content of the comment
	Post& getPost(); //returns the post that this comment is on.
};






#endif