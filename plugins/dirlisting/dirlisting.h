/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Monkey HTTP Daemon
 *  ------------------
 *  Copyright (C) 2001-2009, Eduardo Silva P.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/* dir_html.c */
#ifndef MK_DIRHTML_H
#define MK_DIRHTML_H

#define MK_DIRHTML_URL "/_mktheme"
#define MK_DIRHTML_DEFAULT_MIME "text/html\r\n"

/* For every directory requested, don't send more than
 * this limit of entries.
 */
#define MK_DIRHTML_BUFFER_LIMIT 30
#define MK_DIRHTML_BUFFER_GROW 5

#define MK_HEADER_CHUNKED "Transfer-Encoding: Chunked\r\n\r\n"

/* Theme files */
#define MK_DIRHTML_FILE_HEADER "header.theme"
#define MK_DIRHTML_FILE_ENTRY "entry.theme"
#define MK_DIRHTML_FILE_FOOTER "footer.theme"

#define MK_DIRHTML_TAG_INIT "%_"
#define MK_DIRHTML_TAG_END "_%"
#define MK_DIRHTML_SIZE_DIR "-"

char *_tags_global[] = { "%_html_title_%",
    "%_theme_path_%",
    NULL
};

char *_tags_entry[] = { "%_target_title_%",
    "%_target_url_%",
    "%_target_name_%",
    "%_target_time_%",
    "%_target_size_%",
    NULL
};

struct plugin_api *mk_api;

struct mk_f_list
{
    char *name;
    char *size;
    char *ft_modif;
    unsigned char type;
    struct file_info info;
    struct mk_f_list *next;
};

/* Main configuration of dirhtml module */
struct dirhtml_config
{
    char *theme;
    char *theme_path;
};


mk_pointer mk_dirhtml_default_mime;

/* Global config */
struct dirhtml_config *dirhtml_conf;

/* Used to keep splitted content of every template */
struct dirhtml_template
{
    char *buf;
    int tag_id;
    int len;
    struct dirhtml_template *next;
    char **tags;                /* array of theme tags: [%_xaa__%, %_xyz_%] */
};

/* Templates for header, entries and footer */
struct dirhtml_template *mk_dirhtml_tpl_header;
struct dirhtml_template *mk_dirhtml_tpl_entry;
struct dirhtml_template *mk_dirhtml_tpl_footer;

struct dirhtml_value
{
    int tag_id;
    mk_pointer sep;             /* separator code after value */

    /* string data */
    int len;
    char *value;

    /* next node */
    struct dirhtml_value *next;

    char **tags;                /* array of tags which values correspond */
};

struct dirhtml_value *mk_dirhtml_value_global;

/* Configuration struct */
struct mk_config *conf;

char *check_string(char *str);
char *read_header_footer_file(char *file_path);

int mk_dirhtml_conf();
char *mk_dirhtml_load_file(char *filename);

struct dirhtml_template *mk_dirhtml_template_create(char *content);

struct dirhtml_template
    *mk_dirhtml_template_list_add(struct dirhtml_template **header,
                                  char *buf, int len, char **tpl, int tag);

int mk_dirhtml_init(struct client_session *cs, struct session_request *sr);
int mk_dirhtml_read_config(char *path);
int mk_dirhtml_theme_load();
int mk_dirhtml_theme_debug(struct dirhtml_template **st_tpl);

struct dirhtml_value *mk_dirhtml_tag_assign(struct dirhtml_value **values,
                                            int tag_id, mk_pointer sep,
                                            char *value, char **tags);

struct f_list *get_dir_content(struct session_request *sr, char *path);


#endif
