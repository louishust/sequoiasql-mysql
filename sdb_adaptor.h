/* Copyright (c) 2018, SequoiaDB and/or its affiliates. All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

#ifndef SDB_ADAPTOR__H
#define SDB_ADAPTOR__H

#include <map>
#include <mysql/psi/mysql_thread.h>
#include <my_global.h>
#include <atomic_class.h>
#include "include/client.hpp"
#include "sdb_conn_ptr.h"
#include "sdb_cl_ptr.h"
#include "sdb_util.h"

class sdb_adaptor
{
public:

   ~sdb_adaptor() ;

   static sdb_adaptor *get_instance() ;

   int get_sdb_cl( my_thread_id tid, char *cs_name,
                   char *cl_name, sdb_cl_auto_ptr &collection,
                   bool create = TRUE ) ;

   int create_sdb_cl( my_thread_id tid, char *cs_name,
                      char *cl_name, sdb_cl_auto_ptr &collection ) ;

   int get_sdb_conn( my_thread_id tid, sdb_conn_auto_ptr &sdb_ptr ) ;

   void del_sdb_conn( my_thread_id tid ) ;

private:

   sdb_adaptor() ;

   sdb_adaptor(const sdb_adaptor & rh){}

   sdb_adaptor & operator = (const sdb_adaptor & rh) { return *this ;}

private:
   int                                          conn_max ;
   int                                          clear_num ;
   Atomic_int32                                 conn_num ;
   std::map<my_thread_id, sdb_conn_auto_ptr>    conn_list ;
   pthread_rwlock_t                             rw_mutex ;
} ;

#define SDB_CL_MGR_INST                sdb_adaptor::get_instance()
#define SDB_CONN_MGR_INST              sdb_adaptor::get_instance()

#endif
