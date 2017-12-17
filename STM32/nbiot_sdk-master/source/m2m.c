﻿/**
 * Copyright (c) 2017 China Mobile IOT.
 * All rights reserved.
**/

#include "m2m.h"
#include "struct.h"

uint8_t lwm2m_buffer_send( void    *session,
                           uint8_t *buffer,
                           size_t   length,
                           void     *userdata )
{
#ifdef HAVE_DTLS
    int ret;
    connection_t *conn;
    nbiot_device_t *data;
#else
    int ret;
    size_t sent;
    size_t offset;
    connection_t *conn;
    nbiot_device_t *data;
#endif

    if ( NULL == session ||
         NULL == buffer ||
         NULL == userdata )
    {
        return COAP_500_INTERNAL_SERVER_ERROR;
    }

#ifdef HAVE_DTLS
    conn = (connection_t*)session;
    data = (nbiot_device_t*)userdata;
    ret = dtls_write( &data->dtls,
                      conn->addr,
                      buffer,
                      length );
    if ( -1 == ret )
    {
        return COAP_500_INTERNAL_SERVER_ERROR;
    }
#else
    offset = 0;
    conn = (connection_t*)session;
    data = (nbiot_device_t*)userdata;
    while ( offset < length )
    {
        ret = nbiot_udp_send( data->sock,
                              buffer + offset,
                              length - offset,
                              &sent,
                              conn->addr );
        if ( ret < 0 )
        {
            return COAP_500_INTERNAL_SERVER_ERROR;
        }
        else
        {
            offset += sent;
        }
    }
#endif

    return COAP_NO_ERROR;
}

bool lwm2m_session_is_equal( void *session1,
                             void *session2,
                             void *userdata )
{
    return (session1 == session2);
}

void* lwm2m_connect_server( uint16_t sec_instid,
                            void    *userdata )
{
    const char *uri;
    const char *addr;
    const char *port;
    connection_t *conn;
    nbiot_device_t *dev;

    dev = (nbiot_device_t*)userdata;
    if ( NULL == dev )
    {
        return NULL;
    }

    uri = dev->data.uri;
    if ( NULL == uri )
    {
        return NULL;
    }

    /* parse uri in the form "coaps://[host]:[port]" */
    if ( !nbiot_strncmp(uri,"coaps://",8) )
    {
        addr = uri + 8;
    }
    else if ( !nbiot_strncmp(uri,"coap://",7) )
    {
        addr = uri + 7;
    }
    else
    {
        return NULL;
    }

    port = nbiot_strrchr( addr, ':' );
    if ( NULL == port )
    {
        return NULL;
    }

    /* split string */
    *(char*)port = '\0';
    ++port;

    conn = connection_create( dev->connlist,
                              dev->sock,
                              addr,
                              nbiot_atoi(port--) );
    if ( NULL != conn )
    {
        dev->connlist = conn;
    }

    /* recover */
    *(char*)port = ':';

    return conn;
}

void lwm2m_close_connection( void *session,
                             void *userdata )
{
    connection_t *conn;
    nbiot_device_t *dev;

    if ( NULL == session ||
         NULL == userdata )
    {
        return;
    }

    conn = (connection_t*)session;
    dev = (nbiot_device_t*)userdata;
    dev->connlist = connection_remove( dev->connlist, conn );
}

connection_t* connection_create( connection_t   *connlist,
                                 nbiot_socket_t *sock,
                                 const char     *addr,
                                 uint16_t        port )
{
    int ret;
    connection_t *conn;

    if ( NULL == sock )
    {
        return connlist;
    }

    conn = (connection_t*)nbiot_malloc( sizeof(connection_t) );
    if ( NULL == conn )
    {
        return connlist;
    }

    conn->addr = NULL;
    ret = nbiot_udp_connect( sock,
                             addr,
                             port,
                             &conn->addr );
    if ( ret )
    {
        nbiot_free( conn );

        return connlist;
    }

    conn->next = connlist;
    connlist = conn;

    return connlist;
}

connection_t* connection_find( connection_t           *connlist,
                               const nbiot_sockaddr_t *addr )
{
    connection_t *conn;

    if ( NULL == connlist ||
         NULL == addr )
    {
        return NULL;
    }

    conn = connlist;
    while ( NULL != conn )
    {
        if ( nbiot_sockaddr_equal(conn->addr,addr) )
        {
            return conn;
        }
        else
        {
            conn = conn->next;
        }
    }

    return NULL;
}

connection_t* connection_remove( connection_t *connlist,
                                 connection_t *conn )
{
    connection_t *prev;

    if ( NULL == connlist ||
         NULL == conn )
    {
        return connlist;
    }

    if ( conn == connlist )
    {
        connlist = conn->next;
    }
    else
    {
        prev = connlist;
        while ( NULL != prev &&
                prev->next != conn )
        {
            prev = prev->next;
        }

        if ( NULL != prev )
        {
            prev->next = conn->next;
        }
    }

    nbiot_sockaddr_destroy( conn->addr );
    nbiot_free( conn );

    return connlist;
}

void connection_destroy( connection_t *connlist )
{
    while ( NULL != connlist )
    {
        connection_t *conn;

        conn = connlist;
        connlist = conn->next;

        nbiot_sockaddr_destroy( conn->addr );
        nbiot_free( conn );
    }
}
