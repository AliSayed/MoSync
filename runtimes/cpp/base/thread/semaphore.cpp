/* Copyright (C) 2009 Mobile Sorcery AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

/*
 * File:   semaphore.hpp
 * Author: Ali Mosavian
 *
 * Created on July 14, 2009
 */
#include "semaphore.hpp"
#include "semaphorefactory.hpp"


using namespace Base::Thread;

/**
 * Default constructor
 *
 * @param i     Pointer to the factory
 */
Semaphore::Semaphore ( SemaphoreFactory *i )
: m_factInstance( i )
{

}

/**
 * Copy constructor (not allowed!!)
 *
 */
Semaphore::Semaphore ( const Semaphore &o )
{
    
}

/**
 * Destructor
 *
 */
Semaphore::~Semaphore ( void )
{
    //
    // Tell the factory that I'm no longer live
    //
    if ( m_factInstance != NULL )
        m_factInstance->deleteSemaphore( this );
}

