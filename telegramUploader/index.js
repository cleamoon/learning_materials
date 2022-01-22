const TelegramBot = require("node-telegram-bot-api");
const request = require("request");
const fs = require("fs");

const token = process.env.APITOKEN;
const bot = new TelegramBot(token, {
    polling: true,
}); 

bot.onText(/\/rand/, function (msg) {
    bot.sendMessage(msg.chat.id, Math.random());
});

bot.onText(/\/echo (.+)/, (msg, match) => {
    const chatId = msg.chat.id;
    const resp = match[1];
    console.log(resp);
    bot.sendMessage(chatId, resp);
});

bot.onText(/\/prpr/, function (msg) {
    const chatId = msg.chat.id;
    request("https://konachan.com/post.json?tags=ass&limit=50", 
        function (error, response, body) {
            if (!error && response.statusCode == 200) {
                const result = JSON.parse(body) || [];
                const index = parseInt(Math.random() * result.length);
                bot.sendPhoto(chatId, result[index].file_url, {
                    caption: "手冲一时爽，一直手冲一直爽"
                }).catch((err) => {
                    bot.sendMessage(chatId, "手冲失败");
                })
            } else {
                bot.sendMessage(chatId, "手冲失败");
            }
        }
    );
}); 

bot.onText(/\/upload/, (msg) => {
    const chatId = msg.chat.id;
    var dir = ".";
    const getSortedFiles = async (dir) => {
        const files = await fs.promises.readdir(dir);

        return files
            .map(fileName => ({
                name: fileName,
                time: fs.statSync(`${dir}/${fileName}`).mtime.getTime(),
            })).sort((a, b) => a.time - b.time)
            .map(file => file.name);
    }
    Promise.resolve()
        .then(() => getSortedFiles(dir))
        .then(async function (files) {
            for (const file of files) {
                if (file.endsWith("mp4")) {
                    bot.sendMessage(chatId, file);
                    await new Promise(resolve => setTimeout(resolve, 5000));
                }
            }
        }).catch(console.error);
});