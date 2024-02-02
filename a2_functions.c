/********* definitions.c ********
    Student Name 	= Seyitan Edwards
    Student Number	= 101254690
*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#include <stdbool.h>

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{

   user_t *user = malloc(sizeof(user_t));
   assert(user != NULL);
   strcpy(user->username, username);
   strcpy(user->password, password);
   user->friends = NULL;
   user->posts = NULL;
   user->next = NULL;

   // case for inserting a user at the front
   if (users == NULL)
   {
      users = user;
      return users;
   
   }

   user_t *curr = users;

   if (strcmp(user->username, curr->username) < 0)
   {
      user->next = curr;

      return user;
   }

   while (curr->next != NULL && strcmp(user->username, curr->next->username) > 0)
   {
      curr = curr->next;
   }

   user->next = curr->next;
   curr->next = user;
   return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   user_t *current = users;
   for (; current != NULL; current = current->next)
   {

      if (strcmp(current->username, username) == 0)
      {
         return current;
      }
      else
      {
         continue;
      }
   }
   return NULL;
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *new_friend = malloc(sizeof(friend_t));
   assert(new_friend != NULL);
   strcpy(new_friend->username, username);
   new_friend->next = NULL;

   return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *new_friend = create_friend(friend);

   if (user->friends == NULL || strcmp(new_friend->username, user->friends->username) < 0)
   {
      new_friend->next = user->friends;
      user->friends = new_friend;
   }

   else
   {
      friend_t *curr = user->friends;
      while (curr->next != NULL && strcmp(new_friend->username, curr->username) >= 0)
      {
         curr = curr->next;
      }
      new_friend->next = curr->next;
      curr->next = new_friend;
   }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   if (user->friends == NULL)
   {
      return false;
   }

   friend_t *curr = user->friends;
   friend_t *prev = NULL;

   // Case for the first friend
   if (strcmp(curr->username, friend_name) == 0)
   {
      user->friends = curr->next;
      free(curr);
      return true;
   }

   while (curr != NULL && strcmp(curr->username, friend_name) != 0)
   {
      prev = curr;
      curr = curr->next;
   }
   if (curr != NULL) // friend exists
   {
      prev->next = curr->next;
      free(curr);
      return true;
   }

   return false;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *new_post = malloc(sizeof(post_t));
   assert(new_post != NULL);
   strcpy(new_post->content, text);
   new_post->next = NULL;

   return new_post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   post_t *crpost = user->posts;
   if (user->posts == NULL)
   {
      user->posts = create_post(text);
   }
   else
   {
      crpost = create_post(text);
      crpost->next = user->posts;
      user->posts = crpost;
   }
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   int count = 0;
   post_t *curr = user->posts;
   if (curr == NULL || curr->next == NULL)
   {
      return false;
   }
   while (curr != NULL)
   {
      count++;
      curr = curr->next;
   }

   if (1 > number || count < number)
   {
      return false;
   }

   post_t *temp = user->posts;
   post_t *prev = user->posts;

   if (number == 1)
   {
      user->posts = temp->next;
      free(prev);

      return true;
   }

   for (int i = 1; i < number - 1; i++)
   {
      temp = temp->next;
      prev = temp->next;
   }

   temp = temp->next;
   prev->next = temp->next;

   free(temp);
   return true;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   int num = 1;
   char username[20];
   if (user->posts == NULL)
   {
      printf("------------------------\n");
      printf("%s's posts\n", user->username);
      printf("No posts available for %s\n", user->username);
      printf("------------------------");
   }

   post_t *curr = user->posts;
   while (curr != NULL)
   {
      printf("\n%d-%s\n", num, curr->content);
      num++;
      curr = curr->next;
   }
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   int integer = 1;
   friend_t *friend = user->friends;

   if (friend == NULL)
   {
      printf("\nNo friends available for %s.\n", user->username);
   }

   while (friend != NULL)
   {

      printf("\n%d-%s", integer, friend->username);
      printf("\n%d-%s", integer, friend->posts);
      friend = friend->posts;
      friend = friend->next;
      integer += 1;
   }
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   int max_users = 2;

   for (int user_count = 0; users != NULL && user_count < max_users; users = users->next, user_count++)
   {
      int num = 1;

      post_t *curr = users->posts;
      while (curr != NULL)
      {

         printf("\n%d-%s:  %s", num, users->username, curr->content);
         curr = curr->next;
         num += 1;
      }
   }

   char answer;
   user_t *userd = users;

   while (userd != NULL)
   {

      printf("\nDo you want to display next 2 users posts? (Y/N): ");
      scanf(" %c", &answer);

      if (answer == 'Y' || answer == 'y')
      {

         for (int i = 0; i < 2 && userd != NULL; i++, userd = userd->next)
         {
            int num = 1;
            post_t *curr = userd->posts;

            while (curr != NULL)
            {

               printf("\n%d-%s: %s", num, userd->username, curr->content);
               curr = curr->next;
               num += 1;
            }
         }
      }

      if (answer == 'N' || answer == 'n')
      {
         return;
      }
   }
}

user_t *compare_username_password(user_t *users, const char *username, const char *password)
{
   user_t *curr = users->username;
   user_t *temp = users->password;

   for (; curr != NULL, temp != NULL; curr = curr->next, temp = temp->next)
   {
      if (strcmp(curr, username) == 0 && strcmp(temp, username) == 0)
      {
         return curr;
         return temp;
      }
      else
      {
         continue;
      }
   }

   return NULL;
}

void link_friend(user_t *users, char *username)
{
   user_t *curr = users->friends;

   for (; curr != NULL; curr = curr->next)
   {
      user_t *temp = users;

      for (; temp != NULL; temp = temp->next)
      {
         if (strcmp(temp->username, username) == 0)
         {
            curr->posts = temp->posts;

            break;
         }
      }
   }
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   user_t *user_delete;
   friend_t *friend_delete;
   post_t *post_delete;
   while (users != NULL)
   {

      while (users->friends != NULL)
      {
         friend_delete = users->friends;
         users->friends = users->friends->next;
         free(friend_delete);
      }
      while (users->posts != NULL)
      {
         post_delete = users->posts;
         users->posts = users->posts->next;
         free(post_delete);
      }

      user_delete = users;
      users = users->next;
      free(user_delete);
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu(user_t *user)
{
   printf("\n****************************************************");
   printf("\n                    Welcome %s                          ", user->username);
   printf("\n****************************************************");
   printf("\n1. Register a new user");
   printf("\n2. Manage a user's profile (change password)");
   printf("\n3. Manage a user's post (display/add/remove)");
   printf("\n4. Manage a user's friend (display/add/remove)");
   printf("\n5. Display All Posts");
   printf("\n6. Exit\n");
}

void print_mainmenu()
{
   printf("\n****************************************************");
   printf("\n                    MAIN MENU:                          ");
   printf("\n****************************************************");
   printf("\n1. Register a new user");
   printf("\n2. Logiin with existing user's information");
   printf("\n3. Exit");
}
/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}
