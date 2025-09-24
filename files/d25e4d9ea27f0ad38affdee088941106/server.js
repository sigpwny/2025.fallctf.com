const express = require('express');
const { urlencoded } = require('body-parser');
const puppeteer = require('puppeteer');
const crypto = require('crypto');
const fs = require('fs');
const { inHTMLData } = require('xss-filters');

const secret_endpoint = crypto.randomBytes(32).toString('hex');
const secret_revenge_endpoint = crypto.randomBytes(32).toString('hex');

const port = 1337;

const app = express();

const flags = fs.readFileSync('flag.txt', 'utf8').split('\n');

app.use(urlencoded({ extended: false }));
app.set('view engine', 'ejs');

app.get('/', async function (req, res) {
    res.render('index', { endpoint: 'submit', message: `Please don't submit embezzlement requests. We won't give you money.` });
});

app.get('/rematch', async function (req, res) {
    res.render('index', { endpoint: 'submit-rematch', message: `There's an old saying in Tennessee—I know it's in Texas, probably in Tennessee—that says, 'Fool me once, shame on... shame on you. Fool me—you can't get fooled again.'` });
});

app.get('/revenge', async function (req, res) {
    res.render('index', { endpoint: 'submit-revenge', message: `FTX, the everything app!` });
});

// endpoint for only admin to access your name idea (finding this is not meant to be the challenge)
app.get('/' + secret_endpoint, function (req, res) {
    const message = req.query.message ?? '';
    const title = req.query.title ?? '';

    res.render('view', { title, message, note: `Reminder: please do not accept embezzlement requests from the public form. ${flags[1]}` });
});

// endpoint for only admin to access your name idea (finding this is not meant to be the challenge)
app.get('/' + secret_revenge_endpoint, function (req, res) {
    const message = req.query.message ?? '';
    const title = req.query.title ?? '';

    res.set('Content-Security-Policy', `script-src data:`);
    res.render('view', { title, message, note: `Reminder: please do not accept embezzlement requests from the public form. ${flags[1]}` });
});

// simulate the admin opening your feedback message
async function admin(title, message, ep = secret_endpoint) {
    const browser = await puppeteer.launch({ args: ['--no-sandbox'] });
    const page = await browser.newPage();

    let didpopup = false;
    page.on('dialog', async dialog => {
        didpopup = true;
        await dialog.accept();
    });

    await page.setExtraHTTPHeaders({ 'is-bot': 'true' });

    await page.setDefaultNavigationTimeout(3000);

    try {
        const a = await page.goto(`http://localhost:${port}/${ep}?title=${encodeURIComponent(title)}&message=${encodeURIComponent(message)}`, {
            waitUntil: 'networkidle0'
        });
        await page.waitForDelay(2000);
    } catch (e) {
        // console.error(e);
    } finally {
        await page.close();
        await browser.close();
    }

    return didpopup;
}

// endpoint for you to submit your feedback message to the admin
app.get('/submit', async (req, res) => {
    // check if the request is from the bot (prevent infinite looping)
    if (req.headers['is-bot']) {
        return res.render('view', { message: 'hey!', note: '' });
    }

    // get parameters from the the form you submitted
    const message = req.query['message'] ?? '';
    const title = req.query['title'] ?? '';

    // simulate the admin opening your name idea
    const didpopup = await admin(title, message);

    // send you back your own name idea so you can preview what the admin saw
    if (didpopup) {
        return res.render('view', { title, message, note: `The admin decided to accept your request because they were confused by your alert. ${flags[0]}` });
    } else {
        return res.render('view', { title, message, note: `Your feedback has been carefully reviewed by the admin's trash bin.` });
    }
});

// endpoint for you to submit your feedback message to the admin
app.get('/submit-rematch', async (req, res) => {
    // check if the request is from the bot (prevent infinite looping)
    if (req.headers['is-bot']) {
        return res.render('view', { message: 'hey!', note: '' });
    }

    // get parameters from the the form you submitted
    const original_message = req.query['message'] ?? '';
    const title = req.query['title'] ?? '';

    // nice try! top FTX engineers have been hard at work to secure its funds
    const message = inHTMLData(original_message);

    // simulate the admin opening your name idea
    const didpopup = await admin(title, message);

    // send you back your own name idea so you can preview what the admin saw
    if (didpopup) {
        return res.render('view', { title, message, note: `The admin decided to accept your request because they were confused by your alert. ${flags[2]}` });
    } else {
        return res.render('view', { title, message, note: `Your feedback has been carefully reviewed by the admin's trash bin.` });
    }
});

// endpoint for you to submit your feedback message to the admin
app.get('/submit-revenge', async (req, res) => {
    // check if the request is from the bot (prevent infinite looping)
    if (req.headers['is-bot']) {
        return res.render('view', { message: 'hey!', note: '' });
    }

    // get parameters from the the form you submitted
    const original_message = req.query['message'] ?? '';
    const title = req.query['title'] ?? '';

    // nice try! top FTX engineers have been hard at work to secure its funds
    const message = inHTMLData(original_message);

    // simulate the admin opening your name idea
    const didpopup = await admin(title, message, secret_revenge_endpoint);

    res.set('Content-Security-Policy', `script-src data:`);

    // send you back your own name idea so you can preview what the admin saw
    if (didpopup) {
        return res.render('view', { title, message, note: `The admin decided to accept your request because they were confused by your alert. ${flags[3]}` });
    } else {
        return res.render('view', { title, message, note: `Your feedback has been carefully reviewed by the admin's trash bin.` });
    }
});

app.listen(port, function () {
    console.log('Listening on port ' + port);
});
