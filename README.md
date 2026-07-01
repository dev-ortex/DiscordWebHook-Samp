# 🔗 Discord Webhook

A Pawn include for connecting your **SA-MP/Open.MP** server to **Discord** using webhooks.
Ideal for server logs, admin actions, ban logs, connection logs, automated messages, and custom Discord embeds.

---

## 📦 Installation

1. Download the latest version of `discord_webhook.inc`.
2. Place the file inside your server’s `include/` folder.
3. Install the required dependency:

```bash
sampctl package install Southclaws/pawn-requests
```

4. Add the plugin to your server.

For `server.cfg`:

```cfg
plugins requests
```

For Open.MP `config.json`:

```json
{
    "pawn": {
        "legacy_plugins": [
            "requests"
        ]
    }
}
```

5. Include it in your gamemode or filterscript:

```pawn
#include <discord_webhook>
```

---

## ⚙️ Functions

```pawn
stock DiscordHook_Create(const hookname[], const webhook_url[]);
stock DiscordHook_Find(const hookname[]);

stock Discord_SendMessage(const hookname[], const message[], const callback[] = "");

stock DiscordEmbed_Clear();

stock DiscordEmbed_SetTitle(const title[]);
stock DiscordEmbed_SetDescription(const description[]);
stock DiscordEmbed_SetColor(color);

stock DiscordEmbed_SetAuthor(const name[], const url[], const icon_url[]);
stock DiscordEmbed_SetThumbnail(const url[]);
stock DiscordEmbed_SetImage(const url[]);
stock DiscordEmbed_SetFooter(const text[], const icon_url[]);

stock Discord_AddField(const name[], const value[], bool:inline = false);

stock DiscordEmbed_Send(const hookname[], const callback[] = "");
```

> [!IMPORTANT]
>
> * `hookname`: Internal name used to identify a registered webhook.
> * `webhook_url`: Discord webhook URL from your Discord channel.
> * `callback`: Optional request callback used to handle HTTP responses.
> * `inline`: Defines whether the embed field should appear side by side with other fields.
> * Always call `DiscordEmbed_Clear()` before creating a new embed.

---

## 🧠 Embed Properties

| Function                      | Description                               |
| ----------------------------- | ----------------------------------------- |
| `DiscordEmbed_SetTitle`       | Sets the embed title                      |
| `DiscordEmbed_SetDescription` | Sets the embed description                |
| `DiscordEmbed_SetColor`       | Sets the embed side color                 |
| `DiscordEmbed_SetAuthor`      | Sets the embed author name, URL, and icon |
| `DiscordEmbed_SetThumbnail`   | Sets the small image on the top-right     |
| `DiscordEmbed_SetImage`       | Sets the main embed image                 |
| `Discord_AddField`            | Adds a field to the embed                 |
| `DiscordEmbed_SetFooter`      | Sets the embed footer text and icon       |
| `DiscordEmbed_Send`           | Sends the current embed to Discord        |

---

## 🧪 Example Usage

```pawn
public OnGameModeInit()
{
    DiscordHook_Create(
        "logs",
        "https://discord.com/api/webhooks/YOUR_WEBHOOK_URL"
    );

    Discord_SendMessage("logs", "✅ Server started successfully!");
    return 1;
}
```

---

## 🧩 Complete Embed Example

```pawn
CMD:testembed(playerid)
{
    DiscordEmbed_Clear();

    DiscordEmbed_SetTitle("🚀 Complete Embed Test");
    DiscordEmbed_SetDescription("This embed was sent from a SA-MP/Open.MP server using Discord Webhook.");
    DiscordEmbed_SetColor(0x3498DB);

    DiscordEmbed_SetAuthor(
        "Server Roleplay",
        "https://discord.gg/yourserver",
        "https://i.imgur.com/example.png"
    );

    DiscordEmbed_SetThumbnail("https://i.imgur.com/example.png");
    DiscordEmbed_SetImage("https://i.imgur.com/example.png");

    Discord_AddField("Server", "Server Roleplay", true);
    Discord_AddField("Status", "Online", true);
    Discord_AddField("Players", "15/100", true);
    Discord_AddField("Version", "0.1 Beta", true);
    Discord_AddField("Message", "The Discord log system is working correctly.", false);

    DiscordEmbed_SetFooter(
        "Log System • Server Roleplay",
        "https://i.imgur.com/example.png"
    );

    DiscordEmbed_Send("logs");

    SendClientMessage(playerid, -1, "[Discord] Embed sent successfully.");
    return 1;
}
```

---

## 📝 Ban Log Example

```pawn
stock Discord_LogBan(playerid, adminid, const reason[])
{
    new playerName[MAX_PLAYER_NAME];
    new adminName[MAX_PLAYER_NAME];

    GetPlayerName(playerid, playerName, sizeof(playerName));
    GetPlayerName(adminid, adminName, sizeof(adminName));

    DiscordEmbed_Clear();

    DiscordEmbed_SetTitle("🚨 Ban Log");
    DiscordEmbed_SetDescription("A player has been banned from the server.");
    DiscordEmbed_SetColor(0xFF0000);

    Discord_AddField("Player", playerName, true);
    Discord_AddField("Admin", adminName, true);
    Discord_AddField("Reason", reason, false);

    DiscordEmbed_SetFooter("Administrative System", "");

    DiscordEmbed_Send("logs");

    return 1;
}
```

---

## 📌 Discord Embed Limits

| Item                   | Limit           |
| ---------------------- | --------------- |
| Title                  | 256 characters  |
| Description            | 4096 characters |
| Fields per embed       | 25              |
| Field name             | 256 characters  |
| Field value            | 1024 characters |
| Footer text            | 2048 characters |
| Author name            | 256 characters  |
| Embeds per message     | 10              |
| Total embed characters | 6000            |

---

## ⚠️ Notes

> [!WARNING]
>
> Never expose your Discord webhook URL in public repositories.

Anyone with your webhook URL can send messages to your Discord channel.
If your webhook URL is leaked, delete it from Discord and create a new one.

---

## 📷 Photo Video

https://github.com/user-attachments/assets/f2e69247-5c85-449b-88d9-ae2392ca3c20

---

## 🙌 Credits

* **Ortex** – Original author and developer of the include.

---

## 🌐 Other Languages

* [Português](https://github.com/dev-ortex/discord-webhook/blob/main/README-pt.md)
* [English](https://github.com/dev-ortex/discord-webhook/blob/main/README.md)
