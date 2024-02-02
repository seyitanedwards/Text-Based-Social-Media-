/********* main.c ********
    Student Name 	= Seyitan Edwards
    Student Number	= 101254690
*/

// Includes go here
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{

  /******** DONT MODIFY THIS PART OF THE CODE ********/
  /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE
     AND GENERATE THE STARTING LINKED LIST.
  */
  FILE *csv_file = fopen("user_details.csv", "r");
  if (csv_file == NULL)
  {
    perror("Error opening the CSV file");
    return 1;
  }
  // Parse CSV data and create users
  user_t *users = read_CSV_and_create_users(csv_file, 50);

  fclose(csv_file);
  /******** DONT MODIFY THIS PART OF THE CODE ********/

  /* IMPORTANT: You must use the users linked list created in the code above.
                Any new users should be added to that linked list.
  */

  // Your solution goes here
  printf("\n****************************************************");
  printf("\n        Welcome to Text-Based Faceboook             ");
  printf("\n****************************************************\n");

  _Bool new_exit = false;
  while (new_exit == false)
  {
    //----MAIN MENU----
    print_mainmenu();

    char username[20];
    char password[15];
    int choose;
    int num;

    //---Choice 1(Register New User)
    if (choose = 1)
    {
      printf("Enter a username: ");
      scanf("%s", username);
      user_t *found_user = find_user(users, username);

      if (found_user == NULL)
      {
        printf("Enter an upto 15 characters password: \n");
        scanf("%s", password);
        users = add_user(users, username, password);
        printf("\n****   User Added!   ****\n");
      }
      else
      {
        printf("User Already Exists!");
      }
    }
    //----Choice 2(Login)
    if (choose == 2)
    {
      printf("\nEnter a username: ");
      scanf("%s", username);
      printf("\nEnter your password: ");
      scanf("%s", password);

      user_t *user_exists = compare_username_password(users, username, password);

      if (user_exists == NULL)
      {
        printf("User does not exist!");
      }
      // The user exists
      else
      {
        user_t *found_user = find_user(users, username);
        print_menu(found_user); // Main menu

        printf("Enter your choice: ");
        scanf("%d", &num);
        //----Choice 1 for User
        if (num == 1)
        {
          if (found_user == NULL)
          {
            printf("\n------------------------------------");
            printf("\n         User not found.            ");
            printf("\n------------------------------------\n");
          }

          else
          {
            printf("\nEnter a new password that is upto 15 characters: \n");
            scanf("%s", password);
            strcpy(found_user->password, password);
            printf("\n**** Password changed! ****\n");
          }
        }
        //----Choice 2 for User
        if (num == 2)
        {
          if (found_user != NULL)
          {
            display_user_posts(found_user);
          }

          if (found_user == NULL)
          {
            printf("\n-----------------------------------------------");
            printf("\n                User not found.                ");
            printf("\n-----------------------------------------------");
          }
          _Bool Choice_Exit = false;
          while (Choice_Exit == false)
          {
            int choice = 0;
            printf("\n1. Add a new user post");
            printf("\n2. Remove a users post");
            printf("\n3. Return to main menu");
            printf("\nYour choice: \n");
            scanf("%d", &choice);

            // Add Post
            if (choice == 1)
            {
              char content[250] = "Random";
              printf("Enter your post content: ");
              scanf(" %[^\n]s", content);
              add_post(found_user, content);
              printf("Post added to your profile");
              printf("\n-----------------------------------------------------");
              printf("\n                      %s's posts\n", found_user->username);
              display_user_posts(found_user);
              printf("\n----------------------------------------------------");
            }
            int number = 0;
            // Remove Post
            if (choice == 2)
            {
              printf("Which post do you want to delete?");
              scanf("%d", &number);

              if (delete_post(found_user, number))
              {
                printf("\n------------------------------------");
                printf("\n             %s's posts", found_user->username);
                display_user_posts(found_user);
                printf("\n------------------------------------\n");
                printf("Post %d was deleted successfully!\n", number);
              }

              else
              {
                printf("Invalid post's number\n");
              }
            }
            // Return to main menu
            if (choice == 3)
            {
              Choice_Exit = true;
            }
          }
        }
        // Choice 3(mangae friends)
        if (num == 3)
        {
          int choice;
          _Bool Choice_Exit = false;

          user_t *found_user = find_user(users, username);

          if (found_user != NULL)
          {
            while (Choice_Exit == false)
            {
              printf("\n------------------------------------\n");
              printf("         %s's friends      ", found_user->username);
              printf("\n------------------------------------\n");
              printf("\n1. Display all user's friends\n");
              printf("2. Add a new friend\n");
              printf("3. Delete a friend\n");
              printf("4. Return to main menu\n");

              printf("Your choice: ");
              scanf("%d", &choice);

              // Display user's friends
              if (choice == 1)
              {
                printf("\nList of %s's friends: \n", found_user->username);
                display_user_friends(found_user);
              }
              // Add a new user's friends
              if (choice == 2)
              {
                printf("\nEnter a new friends' name: ");
                scanf("%s", username);

                if (found_user == NULL)
                {
                  printf("This user does not exist!");
                }
                else
                {

                  add_friend(found_user, username);
                  printf("\nFriend added to the list.\n");
                  // call the function to connect the friend's node with an existing user's posts.
                  link_friend(users, found_user);
                }
              }

              // Remove a user's friends
              if (choice == 3)
              {
                display_user_friends(found_user);
                printf("\nEnter a friend's name to delete: \n");
                scanf("%s", username);
                _Bool friend_deleted = delete_friend(found_user, username);

                if (friend_deleted == true)
                {

                  display_user_friends(found_user);
                }
                else
                {
                  printf("\nInvalid friend's name\n");
                  display_user_friends(found_user);
                }
              }

              // Return to main menu
              if (choice == 4)
              {
                Choice_Exit = true;
              }
            }
          }

          else
          {
            printf("\n-----------------------------------------------");
            printf("\n                User not found.                ");
            printf("\n-----------------------------------------------");
          }
        }

        if (num == 4)
        {
          display_all_posts(users);
        }
        if (num == 5)
        {
          continue;
        }

      } // end of else always put before this
      // exit application
      if (choose == 3)
      {

        printf("\n**************************************************");
        printf("\n     Thank you for using Text-Based Facebook      ");
        printf("\n                      GoodBye!                  ");
        printf("\n**************************************************\n");
        teardown(users);
        new_exit = true;
      }
      _Bool exit_status = false;
      while (exit_status == false)
      {

        //----MENU----
        user_t *found_user = find_user(users, username);
        print_menu(found_user);

        int value; // User's choice in the main menu

        printf("\nEnter your choice: ");
        scanf("%d", &value);
        if (value < 1 || value > 6)
        {
          printf("Invalid choice. Please Try again.\n");
        }

        char username[20];
        char password[15];
        user_t *user;

        //----Choice 1----
        if (value == 1)
        {
          printf("Enter a username: ");
          scanf("%s", username);
          printf("Enter an upto 15 characters password: \n");
          scanf("%s", password);
          users = add_user(users, username, password);
          printf("\n****   User Added!   ****\n");
        }

        // ----Choice  2----
        if (value == 2)
        {
          printf("\nEnter a username: ");
          scanf("%s", username);

          user_t *found_user = find_user(users, username);

          if (found_user == NULL)
          {
            printf("\n------------------------------------");
            printf("\n         User not found.            ");
            printf("\n------------------------------------\n");
          }

          else
          {
            printf("\nEnter a new password that is upto 15 characters: \n");
            scanf("%s", password);
            strcpy(found_user->password, password);
            printf("\n**** Password changed! ****\n");
          }
        }

        // ----- Choice 3 ------
        if (value == 3)
        {
          printf("Enter a username to manage their posts: ");
          scanf("%s", username);

          user_t *found_user = find_user(users, username);

          if (found_user != NULL)
          {
            display_user_posts(found_user);
          }

          if (found_user == NULL)
          {
            printf("\n-----------------------------------------------");
            printf("\n                User not found.                ");
            printf("\n-----------------------------------------------");
          }
          _Bool Choice_Exit = false;
          while (Choice_Exit == false)
          {
            int choice = 0;
            printf("\n1. Add a new user post");
            printf("\n2. Remove a users post");
            printf("\n3. Return to main menu");
            printf("\nYour choice: \n");
            scanf("%d", &choice);

            // Add Post
            if (choice == 1)
            {
              char content[250] = "Random";
              printf("Enter your post content: ");
              scanf(" %[^\n]s", content);
              add_post(found_user, content);
              printf("Post added to your profile");
              printf("\n-----------------------------------------------------");
              printf("\n                      %s's posts\n", found_user->username);
              display_user_posts(found_user);
              printf("\n----------------------------------------------------");
            }
            int number = 0;
            // Remove Post
            if (choice == 2)
            {
              printf("Which post do you want to delete?");
              scanf("%d", &number);

              if (delete_post(found_user, number))
              {
                printf("\n------------------------------------");
                printf("\n             %s's posts", found_user->username);
                display_user_posts(found_user);
                printf("\n------------------------------------\n");
                printf("Post %d was deleted successfully!\n", number);
              }

              else
              {
                printf("Invalid post's number\n");
              }
            }
            // Return to main menu
            if (choice == 3)
            {
              Choice_Exit = true;
            }
          }
        }
        //----Choice 4----
        if (value == 4)
        {
          int choice;

          printf("Enter username to manage their friends: ");
          scanf("%s", username);

          _Bool Choice_Exit = false;

          user_t *found_user = find_user(users, username);

          if (found_user != NULL)
          {
            while (Choice_Exit == false)
            {
              printf("\n------------------------------------\n");
              printf("         %s's friends      ", found_user->username);
              printf("\n------------------------------------\n");
              printf("\n1. Display all user's friends\n");
              printf("2. Add a new friend\n");
              printf("3. Delete a friend\n");
              printf("4. Return to main menu\n");

              printf("Your choice: ");
              scanf("%d", &choice);

              // Display user's friends
              if (choice == 1)
              {
                printf("\nList of %s's friends: \n", found_user->username);
                display_user_friends(found_user);
              }
              // Add a new user's friends
              if (choice == 2)
              {
                printf("\nEnter a new friends' name: ");
                scanf("%s", username);

                add_friend(found_user, username);
                printf("\nFriend added to the list.\n");
              }

              // Remove a user's friends
              if (choice == 3)
              {
                display_user_friends(found_user);
                printf("\nEnter a friend's name to delete: \n");
                scanf("%s", username);
                _Bool friend_deleted = delete_friend(found_user, username);

                if (friend_deleted == true)
                {

                  display_user_friends(found_user);
                }
                else
                {
                  printf("\nInvalid friend's name\n");
                  display_user_friends(found_user);
                }
              }

              if (choice == 4)
              {
                printf("Enter a user to display their posts ");
                scanf("%s", username);
                display_user_friends(found_user);
              }

              // Return to main menu
              if (choice == 5)
              {
                Choice_Exit = true;
              }
            }
          }

          else
          {
            printf("\n-----------------------------------------------");
            printf("\n                User not found.                ");
            printf("\n-----------------------------------------------");
          }
        }

        //----Choice 5----
        if (value == 5)
        {
          display_all_posts(users);
        }

        //----Choice 6----
        if (value == 6)
        {
          exit_status = true;

          printf("\n**************************************************");
          printf("\n     Thank you for using Text-Based Facebook      ");
          printf("\n                      GoodBye!                  ");
          printf("\n**************************************************\n");
          teardown(users); // Quits the application
        }
      }
    }
  }
}
