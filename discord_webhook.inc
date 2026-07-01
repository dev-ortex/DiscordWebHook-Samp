/*

                    oooooooooo.   ooooo  .oooooo..o   .oooooo.     .oooooo.   ooooooooo.   oooooooooo.
                    `888'   `Y8b  `888' d8P'    `Y8  d8P'  `Y8b   d8P'  `Y8b  `888   `Y88. `888'   `Y8b
                     888      888  888  Y88bo.      888          888      888  888   .d88'  888      888
                     888      888  888   `"Y8888o.  888          888      888  888ooo88P'   888      888
                     888      888  888       `"Y88b 888          888      888  888`88b.     888      888
                     888     d88'  888  oo     .d8P `88b    ooo `88b    d88'  888  `88b.   888     d88'
                    o888bood8P'   o888o 8""88888P'   `Y8bood8P'  `Y8bood8P'  o888o  o888o o888bood8P'


        native DiscordHook_Create(const hookname[], const url[]);
        native DiscordHook_GetFreeSlot();
        native DiscordHook_Find(const hookname[]);

        native DiscordEmbed_Clear();
        native Discord_Success(E_HTTP_STATUS:status);

        native DiscordEmbed_SetTitle(const title[]);
        native DiscordEmbed_SetDescription(const description[]);
        native DiscordEmbed_SetColor(color);

        native DiscordEmbed_SetAuthor(const name[], const url[], const icon_url[]);
        native DiscordEmbed_SetThumbnail(const url[]);
        native DiscordEmbed_SetImage(const url[]);
        native DiscordEmbed_SetFooter(const text[], const icon_url[]);

        native Discord_AddField(const name[], const value[], bool:inline = false);

        native Discord_SendMessage(const hookname[], const message[], const callback[] = "Discord_IgnoreResponse");
        native DiscordEmbed_Send(const hookname[], const callback[] = "Discord_IgnoreResponse");

        forward Discord_IgnoreResponse(Request:id, E_HTTP_STATUS:status, Node:node);

*/

#if defined _discord_webhook_included
    #endinput
#endif
#define _discord_webhook_included

#if !defined isnull
	#define isnull(%0) (!(%0[0]) || (%0[0] == '\1' && !(%0[1])))
#endif

#if !defined _inc_requests
	#include <requests>
#endif

/* =============================================================================
    DEFINES
============================================================================= */

#define DISCORD_HOOK_MAX             (16)
#define DISCORD_NAME_HOOK_SIZE       (32)
#define DISCORD_URL_HOOK_SIZE        (256)

#define DISCORD_MAX_FIELDS           (5)
#define DISCORD_TITLE_SIZE           (128)
#define DISCORD_DESC_SIZE            (1024)
#define DISCORD_FIELD_NAME_SIZE      (128)
#define DISCORD_FIELD_VALUE_SIZE     (128)
#define DISCORD_FOOTER_SIZE          (128)
#define DISCORD_AUTHOR_NAME_MAX      (256)
#define DISCORD_URL_MAX              (512)

#define DISCORD_SUCCESS(%0)          (((%0) >= 200) && ((%0) <= 299))

forward Discord_IgnoreResponse(Request:id, E_HTTP_STATUS:status, Node:node);

/* =============================================================================
    ENUMS
============================================================================= */

enum E_DISCORD_EMBED
{
    Discord_Embed_Title[DISCORD_TITLE_SIZE],
    Discord_Embed_Description[DISCORD_DESC_SIZE],
    Discord_Embed_Color,

    Discord_Embed_AuthorName[DISCORD_AUTHOR_NAME_MAX],
    Discord_Embed_AuthorUrl[DISCORD_URL_MAX],
    Discord_Embed_AuthorIconUrl[DISCORD_URL_MAX],

    Discord_Embed_Thumbnail[DISCORD_URL_MAX],
    Discord_Embed_Image[DISCORD_URL_MAX],

    Discord_Embed_FooterText[DISCORD_FOOTER_SIZE],
    Discord_Embed_FooterIcon[DISCORD_FOOTER_SIZE],
};

enum E_DISCORD_FIELD_EMBED
{
    Discord_Embed_Field_Name[DISCORD_FIELD_NAME_SIZE],
    Discord_Embed_Field_Value[DISCORD_FIELD_VALUE_SIZE],
    bool:Discord_Embed_Field_Inline,
    bool:Discord_Embed_Field_Used
};

enum E_DISCORD_HOOK
{
    RequestsClient:Discord_Hooks_Client,
    Discord_Hook_Name[DISCORD_NAME_HOOK_SIZE],
    bool:Discord_Hooks_Used
};


/* =============================================================================
    VARIABLES
============================================================================= */

static
    e_DiscordHook[DISCORD_HOOK_MAX][E_DISCORD_HOOK],
    e_DiscordEmbed[E_DISCORD_EMBED],
    e_DiscordEmbedField[DISCORD_MAX_FIELDS][E_DISCORD_FIELD_EMBED];


/* =============================================================================
    HOOK FUNCTIONS
============================================================================= */

stock DiscordHook_Create(const hookname[], const url[])
{
    new index = DiscordHook_GetFreeSlot();

    if(index == -1)
        return print("[DiscordWebhook] ERRO: Limite maximo de hooks atingido.");

    format(e_DiscordHook[index][Discord_Hook_Name], DISCORD_NAME_HOOK_SIZE, "%s", hookname);

    e_DiscordHook[index][Discord_Hooks_Client] = RequestsClient(url);
    e_DiscordHook[index][Discord_Hooks_Used] = true;
    return 1;
}

static stock DiscordHook_GetFreeSlot()
{
    for(new i = 0; i < DISCORD_HOOK_MAX; i++)
    {
        if(!e_DiscordHook[i][Discord_Hooks_Used])
            return i;
    }

    return -1;
}

static stock DiscordHook_Find(const hookname[])
{
    for(new i = 0; i < DISCORD_HOOK_MAX; i++)
    {
        if(!e_DiscordHook[i][Discord_Hooks_Used])
            continue;

        if(!strcmp(hookname, e_DiscordHook[i][Discord_Hook_Name], true))
            return i;
    }

    return -1;
}


/* =============================================================================
    EMBED FUNCTIONS
============================================================================= */

stock DiscordEmbed_Clear()
{
    new resetEmbed[E_DISCORD_EMBED];
    e_DiscordEmbed = resetEmbed;

    new resetField[E_DISCORD_FIELD_EMBED];

    for(new i = 0; i < DISCORD_MAX_FIELDS; i++)
    {
        e_DiscordEmbedField[i] = resetField;
    }

    return 1;
}

stock Discord_Success(E_HTTP_STATUS:status)
{
    return ((_:status) >= 200 && (_:status) <= 299);
}

stock DiscordEmbed_SetTitle(const title[])
{
    return format(e_DiscordEmbed[Discord_Embed_Title], DISCORD_TITLE_SIZE, "%s", title);
}

stock DiscordEmbed_SetDescription(const description[])
{
    return format(e_DiscordEmbed[Discord_Embed_Description], DISCORD_DESC_SIZE, "%s", description);
}

stock DiscordEmbed_SetColor(color)
{
    return e_DiscordEmbed[Discord_Embed_Color] = color;
}

stock DiscordEmbed_SetAuthor(const name[], const url[], const icon_url[])
{
    format(e_DiscordEmbed[Discord_Embed_AuthorName], DISCORD_AUTHOR_NAME_MAX, "%s", name);
    format(e_DiscordEmbed[Discord_Embed_AuthorUrl], DISCORD_URL_MAX, "%s", url);
    format(e_DiscordEmbed[Discord_Embed_AuthorIconUrl], DISCORD_URL_MAX, "%s", icon_url);
    return 1;
}

stock DiscordEmbed_SetThumbnail(const url[])
{
    return format(e_DiscordEmbed[Discord_Embed_Thumbnail], DISCORD_URL_MAX, "%s", url);
}

stock DiscordEmbed_SetImage(const url[])
{
    return format(e_DiscordEmbed[Discord_Embed_Image], DISCORD_URL_MAX, "%s", url);
}

stock DiscordEmbed_SetFooter(const text[], const icon_url[])
{
    format(e_DiscordEmbed[Discord_Embed_FooterText], DISCORD_FOOTER_SIZE, "%s", text);
    format(e_DiscordEmbed[Discord_Embed_FooterIcon], DISCORD_FOOTER_SIZE, "%s", icon_url);
    return 1;
}




/* =============================================================================
    FIELD FUNCTIONS
============================================================================= */

static stock Discord_FieldGetSlot()
{
    for(new i = 0; i < DISCORD_MAX_FIELDS; i++)
    {
        if(!e_DiscordEmbedField[i][Discord_Embed_Field_Used])
            return i;
    }

    return -1;
}

stock Discord_AddField(const name[], const value[], bool:inline = false)
{
    new index = Discord_FieldGetSlot();

    if(index == -1)
        return print("[DiscordWebhook] ERRO: Limite maximo de fields atingido no embed.");

    format(e_DiscordEmbedField[index][Discord_Embed_Field_Name], DISCORD_FIELD_NAME_SIZE, "%s", name);
    format(e_DiscordEmbedField[index][Discord_Embed_Field_Value], DISCORD_FIELD_VALUE_SIZE, "%s", value);

    e_DiscordEmbedField[index][Discord_Embed_Field_Inline] = inline;
    e_DiscordEmbedField[index][Discord_Embed_Field_Used] = true;
    return 1;
}

static stock Node:Discord_MakeField(index)
{
    return JsonObject(
        "name", JsonString(e_DiscordEmbedField[index][Discord_Embed_Field_Name]),
        "value", JsonString(e_DiscordEmbedField[index][Discord_Embed_Field_Value]),
        "inline", JsonInt(e_DiscordEmbedField[index][Discord_Embed_Field_Inline])
    );
}


/* =============================================================================
    SEND FUNCTION
============================================================================= */

stock Discord_SendMessage(const hookname[], const message[], const callback[] = "Discord_IgnoreResponse")
{
    new id = DiscordHook_Find(hookname);

    if (id == -1)
        return print("[DiscordWebhook] ERRO: Hook nao encontrado.");

    if (isnull(message))
        return print("[DiscordWebhook] ERRO: Mensagem vazia.");

    RequestJSON(
        e_DiscordHook[id][Discord_Hooks_Client],
        "?wait=true",
        HTTP_METHOD_POST,
        callback,
        JsonObject(
            "content", JsonString(message)
        )
    );

    return 1;
}

stock DiscordEmbed_Send(const hookname[], const callback[] = "Discord_IgnoreResponse")
{
    new id = DiscordHook_Find(hookname);

    if(id == -1)
        return print("[DiscordWebhook] ERRO: Webhook nao encontrado.");

    new Node:fields = JsonArray();
    for(new i = 0; i < DISCORD_MAX_FIELDS; i++)
        if(e_DiscordEmbedField[i][Discord_Embed_Field_Used])
            fields = JsonAppend(fields, JsonArray(Discord_MakeField(i)));
            
    RequestJSON(
        e_DiscordHook[id][Discord_Hooks_Client],
        "?wait=true",
        HTTP_METHOD_POST,
        callback,
        JsonObject(
            "embeds", JsonArray(
                JsonObject(
                    "title", JsonString(e_DiscordEmbed[Discord_Embed_Title]),
                    "description", JsonString(e_DiscordEmbed[Discord_Embed_Description]),
                    "color", JsonInt(e_DiscordEmbed[Discord_Embed_Color]),

                    "author", JsonObject(
                        "name", JsonString(e_DiscordEmbed[Discord_Embed_AuthorName]),
                        "url", JsonString(e_DiscordEmbed[Discord_Embed_AuthorUrl]),
                        "icon_url", JsonString(e_DiscordEmbed[Discord_Embed_AuthorIconUrl])
                    ),

                    "thumbnail", JsonObject(
                        "url", JsonString(e_DiscordEmbed[Discord_Embed_Thumbnail])
                    ),

                    "image", JsonObject(
                        "url", JsonString(e_DiscordEmbed[Discord_Embed_Image])
                    ),

                    "fields", fields,

                    "footer", JsonObject(
                        "text", JsonString(e_DiscordEmbed[Discord_Embed_FooterText]),
                        "icon_url", JsonString(e_DiscordEmbed[Discord_Embed_FooterIcon])
                    )
                )
            )
        )
    );

    return 1;
}

public Discord_IgnoreResponse(Request:id, E_HTTP_STATUS:status, Node:node)
    return 1;
