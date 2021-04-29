
const path = require('path');
const fs = require('fs');
const { spawn } = require('child_process');

const APP_PATH = path.resolve(__dirname,'..','build','bin');

const bp = require('body-parser').json;
const express = require('express');
const app = express();

app.set('views',__dirname);
app.set('view engine','pug');

app.use(bp());

app.get('/', async (req,res) => {
    res.render('form');
});

app.post('/calc', async (req,res) => {

    let exited = false;
    let calcapp = spawn(path.resolve(APP_PATH,'application'),[],{ cwd : APP_PATH });
    calcapp.on('close', (code) => {

        let cdata;
        if(code === 0)
        {
            let files = fs.readdirSync(APP_PATH);
            files = files.filter(x => path.extname(x) === '.csv');
            cdata = files.map(x => makeDataFromFile(x.split('.')[0]));
        }
        res.json({ code : code, data : cdata });
        exited = true;
    });
    calcapp.on('error', (err) => {
        res.json({ code : 500 });
        exited = true;
    });

    calcapp.stdin.write(req.body.R + '\n');
    calcapp.stdin.write(req.body.W + '\n');
    calcapp.stdin.write(req.body.Step + '\n');
    calcapp.stdin.write(req.body.x0 + '\n');
    calcapp.stdin.write(req.body.y0 + '\n');
    calcapp.stdin.write(req.body.n + '\n');
    calcapp.stdin.write(req.body.k + '\n');

    setTimeout(() => { if(!exited) calcapp.kill(); }, 3000); 

});

app.listen(4451,() => { console.log('Ready....') });

function makeDataFromFile(name)
{
    let text = fs.readFileSync(path.resolve(APP_PATH,`${name}.csv`),'utf-8');
    let lines = text.split('\n');
    let cdata;
    let output;
    if(lines.length > 1)
    {
        lines = lines.filter(l => l.length)
        let tokens = lines.map(l => l.split(';'));
        let n = tokens[0].length;
        let cols = [];
        for(let i = 0; i < n; ++i) cols.push([]);
        tokens.map(t => { for(let i = 0; i < n; ++i) cols[i].push(t[i]); });
        cdata = cols;
        output = { name : name, content : cdata };
    }

    return output;
}
