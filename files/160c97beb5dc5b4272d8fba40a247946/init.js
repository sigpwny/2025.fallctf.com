const crypto = require('crypto');

module.exports.createAdminUser = async function createAdminUser(db) {
    const randomPassword = crypto.randomBytes(16).toString('hex');

    try {
        const users = db.collection('users');

        await users.createIndex({ username: 1 }, { unique: true });

        await users.insertOne({
            username: 'admin',
            password: randomPassword,
            role: 'admin',
            createdAt: new Date()
        });

        console.log(`Admin user created with password: ${randomPassword}`);
    }
    catch (e) {
        // console.error(e);
    }
}
