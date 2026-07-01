# 🔗 Discord Webhook

Uma include em Pawn para conectar seu servidor **SA-MP/Open.MP** ao **Discord** usando webhooks.
Ideal para logs do servidor, ações administrativas, logs de banimento, conexões de jogadores, mensagens automáticas e embeds personalizados.

---

## 📦 Instalação

1. Baixe a versão mais recente de `discord_webhook.inc`.
2. Coloque o arquivo dentro da pasta `include` do seu servidor.
3. Instale a dependência necessária:

```bash
sampctl package install Southclaws/pawn-requests
```

4. Adicione o plugin no seu servidor.

No `server.cfg`:

```cfg
plugins requests
```

No `config.json` do Open.MP:

```json
{
    "pawn": {
        "legacy_plugins": [
            "requests"
        ]
    }
}
```

5. Inclua no seu gamemode ou filterscript:

```pawn
#include <discord_webhook>
```

---

## ⚙️ Funções

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
> * `hookname`: nome interno usado para identificar um webhook registrado.
> * `webhook_url`: URL do webhook criada no canal do Discord.
> * `callback`: callback opcional para tratar a resposta da requisição HTTP.
> * `inline`: define se o field ficará lado a lado com outros fields.
> * Sempre use `DiscordEmbed_Clear()` antes de criar um novo embed.

---

## 🧠 Propriedades do Embed

| Função                        | Descrição                                         |
| ----------------------------- | ------------------------------------------------- |
| `DiscordEmbed_SetTitle`       | Define o título do embed                          |
| `DiscordEmbed_SetDescription` | Define a descrição do embed                       |
| `DiscordEmbed_SetColor`       | Define a cor lateral do embed                     |
| `DiscordEmbed_SetAuthor`      | Define o autor, URL e ícone do embed              |
| `DiscordEmbed_SetThumbnail`   | Define a imagem pequena no canto superior direito |
| `DiscordEmbed_SetImage`       | Define a imagem principal do embed                |
| `Discord_AddField`            | Adiciona um campo ao embed                        |
| `DiscordEmbed_SetFooter`      | Define o rodapé e o ícone do embed                |
| `DiscordEmbed_Send`           | Envia o embed atual para o Discord                |

---

## 🧪 Exemplo de Uso

```pawn
public OnGameModeInit()
{
    DiscordHook_Create(
        "logs",
        "https://discord.com/api/webhooks/SEU_WEBHOOK_AQUI"
    );

    Discord_SendMessage("logs", "✅ Servidor iniciado com sucesso!");
    return 1;
}
```

---

## 🧩 Exemplo Completo de Embed

```pawn
CMD:testembed(playerid)
{
    DiscordEmbed_Clear();

    DiscordEmbed_SetTitle("🚀 Teste de Embed Completo");
    DiscordEmbed_SetDescription("Este embed foi enviado por um servidor SA-MP/Open.MP usando Discord Webhook.");
    DiscordEmbed_SetColor(0x3498DB);

    DiscordEmbed_SetAuthor(
        "Server Roleplay",
        "https://discord.gg/seuservidor",
        "https://i.imgur.com/exemplo.png"
    );

    DiscordEmbed_SetThumbnail("https://i.imgur.com/exemplo.png");
    DiscordEmbed_SetImage("https://i.imgur.com/exemplo.png");

    Discord_AddField("Servidor", "Server Roleplay", true);
    Discord_AddField("Status", "Online", true);
    Discord_AddField("Jogadores", "15/100", true);
    Discord_AddField("Versão", "0.1 Beta", true);
    Discord_AddField("Mensagem", "O sistema de logs do Discord está funcionando corretamente.", false);

    DiscordEmbed_SetFooter(
        "Sistema de Logs • Server Roleplay",
        "https://i.imgur.com/exemplo.png"
    );

    DiscordEmbed_Send("logs", "OnDiscordResponse");

    SendClientMessage(playerid, -1, "[Discord] Embed enviado, aguardando resposta da callback.");
    return 1;
}

forward OnDiscordResponse(Request:id, E_HTTP_STATUS:status, Node:node);
public OnDiscordResponse(Request:id, E_HTTP_STATUS:status, Node:node)
{
    if(Discord_Success(status))
        return printf("[Discord] Embed enviado com sucesso. Status: %d", _:status);
    
    printf("[Discord] Falha ao enviar embed. Status: %d", _:status);
    return 1;
}
```

---

## 📝 Exemplo de Log de Banimento

```pawn
stock Discord_LogBan(playerid, adminid, const reason[])
{
    new playerName[MAX_PLAYER_NAME];
    new adminName[MAX_PLAYER_NAME];

    GetPlayerName(playerid, playerName, sizeof(playerName));
    GetPlayerName(adminid, adminName, sizeof(adminName));

    DiscordEmbed_Clear();

    DiscordEmbed_SetTitle("🚨 Log de Banimento");
    DiscordEmbed_SetDescription("Um jogador foi banido do servidor.");
    DiscordEmbed_SetColor(0xFF0000);

    Discord_AddField("Jogador", playerName, true);
    Discord_AddField("Admin", adminName, true);
    Discord_AddField("Motivo", reason, false);

    DiscordEmbed_SetFooter("Sistema Administrativo", "");

    DiscordEmbed_Send("logs");

    return 1;
}
```

---

## ⚠️ Observações

> [!WARNING]
>
> Nunca exponha a URL do seu webhook em repositórios públicos.

Qualquer pessoa com acesso à URL do webhook pode enviar mensagens no seu canal do Discord.
Se sua URL for vazada, exclua o webhook no Discord e crie outro.

---

## 📷 Photo de Demonstração

https://github.com/user-attachments/assets/aff4fe48-9f1a-479a-b8de-6dbe393138d5

---

## 🙌 Créditos

* **Ortex** – Autor original e desenvolvedor da include.

---

## 🌐 Outros Idiomas

* [Português](https://github.com/dev-ortex/DiscordWebHook-Samp/blob/main/README-pt.md)
* [English](https://github.com/dev-ortex/DiscordWebHook-Samp/blob/main/README.md)