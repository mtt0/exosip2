/*
  eXosip - This is the eXtended osip library.
  Copyright (C) 2002, 2003  Aymeric MOIZARD  - jack@atosc.org
  
  eXosip is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  eXosip is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifdef ENABLE_MPATROL
#include <mpatrol.h>
#endif

#ifndef __EXOSIP2_H__
#define __EXOSIP2_H__

#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#define snprintf _snprintf
#define close(s) closesocket(s)
#endif

#include <stdio.h>

#include <osip2/osip.h>
#include <osip2/osip_dialog.h>
#include <osip2/osip_negotiation.h>

#include <eXosip/eXosip_cfg.h>
#include <eXosip/eXosip.h>

#ifndef JD_EMPTY

#define JD_EMPTY          0
#define JD_INITIALIZED    1
#define JD_TRYING         2
#define JD_QUEUED         3
#define JD_RINGING        4
#define JD_ESTABLISHED    5
#define JD_REDIRECTED     6
#define JD_AUTH_REQUIRED  7
#define JD_CLIENTERROR    8
#define JD_SERVERERROR    9
#define JD_GLOBALFAILURE  10
#define JD_TERMINATED     11

#define JD_MAX            11

#endif

#ifdef __cplusplus
extern "C"
{
#endif

void  eXosip_update();

typedef struct eXosip_dialog_t eXosip_dialog_t;

struct eXosip_dialog_t {

  int              d_id;
  int              d_STATE;
  osip_dialog_t   *d_dialog;      /* active dialog */

  int              d_timer;
  osip_message_t  *d_200Ok;
  osip_message_t  *d_ack;
  osip_list_t     *media_lines;

  osip_list_t     *d_inc_trs;
  osip_list_t     *d_out_trs;

  /* struct _BodyHandler     *d_bh; */

  eXosip_dialog_t *next;
  eXosip_dialog_t *parent;
};

typedef struct eXosip_subscribe_t eXosip_subscribe_t;

struct eXosip_subscribe_t {

  int                 s_id;
  char                s_uri[255];
  int                 s_online_status;
  int                 s_ss_status;
  int                 s_ss_reason;
  int                 s_ss_expires;
  eXosip_dialog_t    *s_dialogs;

  osip_transaction_t *s_inc_tr;
  osip_transaction_t *s_out_tr;

  eXosip_subscribe_t *next;
  eXosip_subscribe_t *parent;
};

typedef struct eXosip_notify_t eXosip_notify_t;

struct eXosip_notify_t {

  int                 n_id;
  char                n_uri[255];
  int                 n_online_status;
  char                n_contact_info[255];

  int                 n_ss_status;
  int                 n_ss_reason;
  int                 n_ss_expires;
  eXosip_dialog_t    *n_dialogs;

  osip_transaction_t *n_inc_tr;
  osip_transaction_t *n_out_tr;

  eXosip_notify_t    *next;
  eXosip_notify_t    *parent;
};

typedef struct eXosip_call_t eXosip_call_t;

struct eXosip_call_t {

  int                      c_id;
  char                     c_subject[100];
  eXosip_dialog_t         *c_dialogs;
  osip_transaction_t      *c_inc_tr;
  osip_transaction_t      *c_out_tr;
  osip_transaction_t      *c_inc_options_tr;
  osip_transaction_t      *c_out_options_tr;
  void                    *external_reference;

  osip_negotiation_ctx_t  *c_ctx;

  eXosip_call_t           *next;
  eXosip_call_t           *parent;
};


typedef struct eXosip_realm_t eXosip_realm_t;

struct eXosip_realm_t {

  int             r_id;

  char           *r_realm;
  char           *r_username;
  char           *r_passwd;

  eXosip_realm_t *next;
  eXosip_realm_t *parent;
};

typedef struct eXosip_reg_t eXosip_reg_t;

struct eXosip_reg_t {

  int             r_id;

  int             r_reg_period;     /* delay between registration */
  char           *r_aor;            /* sip identity */
  char           *r_registrar;      /* registrar */
  eXosip_realm_t *r_realms;         /* list of realms */
  char           *r_contact;        /* list of contacts string */

  osip_transaction_t  *r_last_tr;
  eXosip_reg_t   *next;
  eXosip_reg_t   *parent;
};


eXosip_event_t *eXosip_event_init_for_call(int type, eXosip_call_t *jc,
					      eXosip_dialog_t *jd);
int eXosip_event_add_sdp_info(eXosip_event_t *je, osip_message_t *message);
int eXosip_event_add_status(eXosip_event_t *je, osip_message_t *response);
eXosip_event_t *eXosip_event_init_for_subscribe(int type,
						   eXosip_subscribe_t *js,
						   eXosip_dialog_t *jd);
eXosip_event_t *eXosip_event_init_for_notify(int type, eXosip_notify_t *jn,
						eXosip_dialog_t *jd);
eXosip_event_t *eXosip_event_init_for_reg(int type, eXosip_reg_t *jr);
int eXosip_event_init(eXosip_event_t **je, int type);
eXosip_call_t *eXosip_event_get_callinfo(eXosip_event_t *je);
eXosip_dialog_t *eXosip_event_get_dialoginfo(eXosip_event_t *je);
eXosip_reg_t *eXosip_event_get_reginfo(eXosip_event_t *je);
eXosip_notify_t *eXosip_event_get_notifyinfo(eXosip_event_t *je);
eXosip_subscribe_t *eXosip_event_get_subscribeinfo(eXosip_event_t *je);
int eXosip_event_add(eXosip_event_t *je);
eXosip_event_t *eXosip_event_wait(int tv_s, int tv_ms);
eXosip_event_t *eXosip_event_get();

typedef void (* eXosip_callback_t) (int type, eXosip_event_t *);

/*  typedef void (* eXosip_call_callback_t) (int type, eXosip_event_t *);
    typedef void (* eXosip_subscribe_callback_t) (int type, eXosip_event_t *);
    typedef void (* eXosip_notify_callback_t) (int type, eXosip_event_t *);
    typedef void (* eXosip_reg_callback_t) (int type, eXosip_event_t *);
*/

typedef struct eXosip_t eXosip_t;

struct eXosip_t {

  FILE               *j_input;
  FILE               *j_output;
  eXosip_call_t      *j_calls;        /* my calls        */
  eXosip_subscribe_t *j_subscribes;   /* my friends      */
  eXosip_notify_t    *j_notifies;     /* my susbscribers */
  osip_list_t        *j_transactions;

  eXosip_reg_t       *j_reg;

  void               *j_mutexlock;
  osip_t             *j_osip;
  int                 j_socket;
  int                 j_stop_ua;
  void               *j_thread;

  jsubscriber_t      *j_subscribers;
  jfriend_t          *j_friends;
  jidentity_t        *j_identitys;

  int                 j_runtime_mode;
  eXosip_callback_t   j_call_callbacks[EXOSIP_CALLBACK_COUNT];
  osip_fifo_t        *j_events;

  osip_negotiation_t  *osip_negotiation;
};

typedef struct jinfo_t jinfo_t;

struct jinfo_t {
  eXosip_dialog_t     *jd;
  eXosip_call_t       *jc;
  eXosip_subscribe_t  *js;
  eXosip_notify_t     *jn;
};



char *eXosip_guess_ip_for_via ();

int  eXosip_sdp_negotiation_init();
sdp_message_t *eXosip_get_local_sdp_info(osip_transaction_t *invite_tr);
sdp_message_t *eXosip_get_remote_sdp_info(osip_transaction_t *invite_tr);
int eXosip_sdp_negotiation_replace(osip_negotiation_t *sn);

int    eXosip_set_callbacks(osip_t *osip);
char  *osip_to_tag_new_random();
unsigned int via_branch_new_random();
void __eXosip_delete_jinfo(osip_transaction_t *transaction);
jinfo_t *__eXosip_new_jinfo(eXosip_call_t *jc, eXosip_dialog_t *jd,
			    eXosip_subscribe_t *js, eXosip_notify_t *jn);

int  eXosip_dialog_init_as_uac(eXosip_dialog_t **jd, osip_message_t *_200Ok);
int  eXosip_dialog_init_as_uas(eXosip_dialog_t **jd, osip_message_t *_invite, osip_message_t *_200Ok);
void eXosip_dialog_free(eXosip_dialog_t *jd);
void eXosip_dialog_set_state(eXosip_dialog_t *jd, int state);
void eXosip_delete_early_dialog(eXosip_dialog_t *jd);

int generating_initial_subscribe(osip_message_t **message, char *to,
				 char *from, char *route);
int generating_message(osip_message_t **message, char *to, char *from,
		       char *route, char *buff);
int  generating_cancel(osip_message_t **dest, osip_message_t *request_cancelled);
int  generating_options_within_dialog(osip_message_t **info, osip_dialog_t *dialog);
int  generating_bye(osip_message_t **bye, osip_dialog_t *dialog);
int  generating_refer(osip_message_t **refer, osip_dialog_t *dialog, char *refer_to);
int  generating_invite_on_hold(osip_message_t **invite, osip_dialog_t *dialog,
				char *subject, char *sdp);
int  generating_invite_off_hold(osip_message_t **invite, osip_dialog_t *dialog,
				char *subject, char *sdp);
int  generating_options(osip_message_t **options, char *from, char *to, char *proxy);
int  generating_info(osip_message_t **info, char *from, char *to, char *proxy);

int  eXosip_reg_init(eXosip_reg_t **jr, char *from, char *proxy, char *contact);
void eXosip_reg_free(eXosip_reg_t *jreg);
int  generating_register(osip_message_t **reg, char *transport, char *from, char *proxy);

int eXosip_call_dialog_find(int jid, eXosip_call_t **jc, eXosip_dialog_t **jd);
int eXosip_notify_dialog_find(int nid, eXosip_notify_t **jn, eXosip_dialog_t **jd);
int eXosip_subscribe_dialog_find(int nid, eXosip_subscribe_t **js, eXosip_dialog_t **jd);
int eXosip_call_find(int cid, eXosip_call_t **jc);
int eXosip_dialog_set_200ok(eXosip_dialog_t *_jd, osip_message_t *_200Ok);

int eXosip_answer_invite_1xx(eXosip_call_t *jc, eXosip_dialog_t *jd, int code);
int eXosip_answer_invite_2xx(eXosip_call_t *jc, eXosip_dialog_t *jd, int code);
int eXosip_answer_invite_3456xx(eXosip_call_t *jc, eXosip_dialog_t *jd, int code);
int eXosip_answer_options_1xx(eXosip_call_t *jc, eXosip_dialog_t *jd, int code);
int eXosip_answer_options_2xx(eXosip_call_t *jc, eXosip_dialog_t *jd, int code);
int eXosip_answer_options_3456xx(eXosip_call_t *jc, eXosip_dialog_t *jd, int code);
void eXosip_notify_answer_subscribe_1xx(eXosip_notify_t *jc,
					eXosip_dialog_t *jd, int code);
void eXosip_notify_answer_subscribe_2xx(eXosip_notify_t *jn,
					eXosip_dialog_t *jd, int code);
void eXosip_notify_answer_subscribe_3456xx(eXosip_notify_t *jn,
					   eXosip_dialog_t *jd, int code);

int _eXosip_build_response_default(osip_message_t **dest, osip_dialog_t *dialog,
				  int status, osip_message_t *request);
int complete_answer_that_establish_a_dialog(osip_message_t *response, osip_message_t *request, char *contact);
int _eXosip_build_request_within_dialog(osip_message_t **dest, char *method_name,
				       osip_dialog_t *dialog, char *transport);

int eXosip_remove_transaction_from_call(osip_transaction_t *tr, eXosip_call_t *jc);
osip_transaction_t *eXosip_find_last_inc_notify(eXosip_subscribe_t *jn, eXosip_dialog_t *jd);
osip_transaction_t *eXosip_find_last_out_notify(eXosip_notify_t *jn, eXosip_dialog_t *jd);
osip_transaction_t *eXosip_find_last_inc_subscribe(eXosip_notify_t *jn, eXosip_dialog_t *jd);
osip_transaction_t *eXosip_find_last_out_subscribe(eXosip_subscribe_t *js, eXosip_dialog_t *jd );

osip_transaction_t *eXosip_find_last_out_options(eXosip_call_t *jc, eXosip_dialog_t *jd );
osip_transaction_t *eXosip_find_last_inc_options(eXosip_call_t *jc, eXosip_dialog_t *jd );
osip_transaction_t *eXosip_find_last_options(eXosip_call_t *jc, eXosip_dialog_t *jd );
osip_transaction_t *eXosip_find_last_invite(eXosip_call_t *jc, eXosip_dialog_t *jd );
osip_transaction_t *eXosip_find_last_inc_invite(eXosip_call_t *jc, eXosip_dialog_t *jd);
osip_transaction_t *eXosip_find_last_out_invite(eXosip_call_t *jc, eXosip_dialog_t *jd);
osip_transaction_t *eXosip_find_last_inc_bye(eXosip_call_t *jc, eXosip_dialog_t *jd);
osip_transaction_t *eXosip_find_last_out_bye(eXosip_call_t *jc, eXosip_dialog_t *jd);
osip_transaction_t *eXosip_find_last_inc_refer(eXosip_call_t *jc, eXosip_dialog_t *jd);
osip_transaction_t *eXosip_find_last_out_refer(eXosip_call_t *jc, eXosip_dialog_t *jd);


int  eXosip_call_init(eXosip_call_t **jc);
void eXosip_call_free(eXosip_call_t *jc);
void __eXosip_call_remove_dialog_reference_in_call(eXosip_call_t *jc, eXosip_dialog_t *jd);
void eXosip_call_set_subject(eXosip_call_t *jc, char *subject);
int  eXosip_read_message(int max_message_nb, int sec_max, int usec_max);
void eXosip_release_terminated_calls ( void );


int  eXosip_subscribe_init(eXosip_subscribe_t **js, char *uri);
void eXosip_subscribe_free(eXosip_subscribe_t *js);
int  _eXosip_subscribe_set_refresh_interval(eXosip_subscribe_t *js, osip_message_t *inc_subscribe);
int  eXosip_subscribe_need_refresh(eXosip_subscribe_t *js, int now);
int eXosip_subscribe_send_subscribe(eXosip_subscribe_t *js,
				    eXosip_dialog_t *jd, const char *expires);

int  eXosip_notify_init(eXosip_notify_t **jn, osip_message_t *inc_subscribe);
void eXosip_notify_free(eXosip_notify_t *jn);
int  _eXosip_notify_set_contact_info(eXosip_notify_t *jn, char *uri);
int  _eXosip_notify_set_refresh_interval(eXosip_notify_t *jn,
					 osip_message_t *inc_subscribe);
void _eXosip_notify_add_expires_in_2XX_for_subscribe(eXosip_notify_t *jn,
						     osip_message_t *answer);
int  _eXosip_notify_add_body(eXosip_notify_t *jn, osip_message_t *notify);
int  eXosip_notify_add_allowed_subscriber(char *sip_url);
int  _eXosip_notify_is_a_known_subscriber(osip_message_t *sip);
int  eXosip_notify_send_notify(eXosip_notify_t *jn, eXosip_dialog_t *jd,
			       int subsciption_status,
			       int online_status);


#ifdef __cplusplus
}
#endif

#endif