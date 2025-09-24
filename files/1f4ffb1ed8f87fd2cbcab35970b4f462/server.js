const express = require('express');
const { MongoClient } = require('mongodb');
const crypto = require('crypto');
const { createAdminUser } = require('./init.js');
const cookieParser = require('cookie-parser');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());
app.use(cookieParser());

app.use((req, res, next) => {
    if (req.cookies && req.cookies['logged-in'] === logged_in_cookie) {
        return res.send(flag);
    }
    next();
});

app.use(express.static(__dirname + '/public'));

const mongodb_password = process.env.MONGODB_PASSWORD;
const mongoUrl = `mongodb://sigpwny:${mongodb_password}@mongodb:27017`;
const client = new MongoClient(mongoUrl);

const logged_in_cookie = crypto.randomBytes(16).toString('hex');
const flag = process.env.FLAG || "fallctf{example_flag}";

async function connectMongo() {
    try {
        await client.connect();
        app.locals.db = client.db("challenge");

        await createAdminUser(app.locals.db);

        if ((await app.locals.db.collection('users').find({}).toArray()).length != 1) {
            console.error('Failed to create admin user');
            process.exit(1); 
        }
    } catch (err) {
        console.error('MongoDB connection error:', err);
        process.exit(1);
    }
}

connectMongo();

app.post('/login', async (req, res) => {
    const db = app.locals.db;
    
    const { username, password } = req.body;
    if (!username || !password) {
        return res.status(400).json({ error: 'Username and password required.' });
    }
    try {
        const user = await db.collection('users').findOne({ username: username, password: password });
        if (!user) return res.status(401).json({ error: 'Incorrect username or password.' })

        res.cookie('logged-in', logged_in_cookie, { httpOnly: true });

        res.json({ message: 'Login successful.' });
    } catch (err) {
        res.status(500).json({ error: err });
    }
});

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});