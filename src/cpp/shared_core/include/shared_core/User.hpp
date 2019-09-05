/*
 * User.hpp
 * 
 * Copyright (C) 2019 by RStudio, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef SHARED_CORE_USER_HPP
#define SHARED_CORE_USER_HPP

#include <string>

#include "PImpl.hpp"

namespace rstudio {
namespace core {

#ifndef _WIN32

typedef uid_t  UidType;
typedef gid_t  GidType;

#endif

class Error;
class FilePath;

/**
 * @brief Class which represents a system user.
 */
class User
{
public:

#ifndef _WIN32
   /**
    * @brief Creates a user by user ID.
    *
    * @param in_userId      The ID of the user to create.
    */
   explicit User(UidType in_userId);

   /**
    * @brief Gets the ID of this user's primary group.
    *
    * @return The ID of this user's primary group.
    */
   GidType getGroupId() const;

   /**
    * @brief Gets the ID of this user.
    *
    * @return The ID of this user.
    */
   UidType getUserId() const;

#endif

   /**
    * @brief Copy constructor.
    *
    * @param in_other   The user to copy.
    */
   User(const User& in_other);

   /**
    * @brief Creates either an empty user or a user object which represents all users. Either way, a user object
    *        constructed this way does not have a user ID, user name, or group ID.
    *
    * @param in_isAllUsers      True if this user should represent all users; false if it should be an empty user.
    *                           Default: false.
    */
   explicit User(bool in_isAllUsers = false);

   /**
    * @brief Creates a user by username.
    *
    * @param in_username    The name of the user.
    */
   explicit User(const std::string& in_username);

   /**
    * @brief Gets the current user.
    *
    * @param out_currentUser    The user this process is currently executing on behalf of. This object will be the empty
    *                           user if this function returns an error.
    *
    * @return Success if the user could be retrieved; Error otherwise.
    */
   static Error getCurrentUser(User& out_currentUser);

   /**
    * @brief Checks whether the user represented by this object exists.
    *
    * If this is an empty user, or is a user object which represents all users, this method will return false as it does
    * not represent a user which exists on the system.
    *
    * @return True if this user exists; false otherwise.
    */
   bool exists() const;

   /**
    * @brief Returns whether this object represents all users or not. See the default constructor for more details.
    *
    * @return True if this object represents all users; false otherwise.
    */
   bool isAllUsers() const;

   /**
    * @brief Checks whether this user is empty or not.
    * @return
    */
   bool isEmpty() const;

   /**
    * @brief Gets the user home path, if it exists.
    *
    * @return The user's home path, if it exists; empty path otherwise.
    */
   const FilePath& getHomePath() const;

   /**
    * @brief Returns the name of this user.
    *
    * @return The name of this user ("*" for all users).
    */
   const std::string& getUsername() const;

   /**
    * @brief Overloaded assignment operator.
    *
    * @param in_other   The user to copy to this one.
    *
    * @return This user.
    */
   User& operator=(const User& in_other);

private:
   // The private implementation of User.
   PRIVATE_IMPL(m_impl);
};

} // namespace core
} // namespace rstudio

#endif