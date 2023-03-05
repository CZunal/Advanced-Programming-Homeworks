#include "SUBook.h"

//Prepared by Can Zunal 29453

vector<Post*> User::getPosts()
{
	return posts;
}

User::~User()
{
	for (int i = 0; i < posts.size(); i++)
	{
		posts[i]->~Post();
	}
	posts.clear();
}

Post& User::createPost(string content)
{
	Post* newPost = new Post(content, this);
	posts.push_back(newPost);
	return *newPost;
}

int User::getNumComments()
{
	return num_comments;
}

string User::getName()
{
	return name;
}

void User::incrementCommentNum()
{
	num_comments += 1;
}

void User::DecrementCommentNum()
{
	num_comments -= 1;

}

Post::~Post()
{
	for (int i = 0; i < comments.size(); i++)
	{

		delete (comments[i]);
	}
	comments.clear();
}

void Post::addComment(string content, User* commenter)
{
	Comment* newComment = new Comment(commenter, content, this);
	commenter->incrementCommentNum();
	comments.push_back(newComment);

}

vector<Comment*> Post::getComments()
{
	return comments;
}

User& Post::getUser()
{
	User& reffUser = *userOfPost;
	return reffUser;
}

string Post::getContent()
{
	return contentOfPost;
}



User& Comment::getUser()
{
	User& referenceUser = *userOfComment;
	return referenceUser;
}


string Comment::getContent()
{
	return contentOfComment;
}

Post& Comment::getPost()
{
	Post& referencePost = *postOfComment;
	return referencePost;
}

Comment::~Comment()
{
	this->getUser().DecrementCommentNum();
}

