#pragma once
#include <vector>
#include <string>

// holds the transaction that occurred
// stuff like post_author id, current_like count, current_comment count, 
// do we store the comments also in the transaction  - hash em and store em?  

// transaction can be literally anything you do on the social media platform
// so rn let's just keep the scope limited to comments, like, dislike and posts

enum class Platform_Interaction_Type{
    Post,
    Vote,   // upvote downvote like reddit
    Comment
};

enum class Post_Interaction_Type{
    Create, Delete, Edit
};

enum class Comment_Interaction_Type{
    Create, Delete, Edit
};

struct Vote{
    // either of the two are gonna be 1 for a transaction
    bool post_voted;
    bool comment_voted;
    //------------------   this will determine what was voted and what id to consider
    uint32_t post_id;
    uint16_t comment_id;
    bool vote_type;   // upvote is 1 downvote is 0
};

struct Post{
    bool post_transaction;
    Post_Interaction_Type post_type;
    uint32_t post_id;    // max uint32 is gonna be like 1 billion+
    uint32_t like_count;
    uint32_t dislike_count;
    uint32_t comment_count;
    std::string post_content_id;  // this is firestore id for text content
    std::string post_media_url;   // this is the url for media in firebase storage
    std::vector<std::string> comment_ids; // this is a vector of comment ids stored on firestore
};

struct Comment{
    bool comment_transaction;
    Comment_Interaction_Type comment_type;
    uint16_t comment_id;    // max uint16 is gonna have an upper limit of some 60k
    uint32_t parent_post_id; // the root comment has to have a parent_post_id
    uint16_t parent_comment_id; // for replies - can be used to nest replies
    uint32_t like_count;
    uint32_t dislike_count;
    uint32_t reply_count;    // every reply is gonna be another comment so really a chain of comments
    std::string comment_content_id;  // this is firestore id for text content
    std::string comment_media_url;   // this is the url for media in firebase storage
    std::vector<std::string> reply_ids; // this is a vector of replies' ids stored on firestore
};

struct Transaction{
    Platform_Interaction_Type interaction_type;
    // can check this based on the bool value in each struct to know which interaction
    Post post;
    Comment comment;
    Vote vote;
    uint32_t transaction_id;
    uint64_t transaction_time;

    uint32_t user_id;  // user who initiated this transaction
};