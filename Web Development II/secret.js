/* 

*/
router.post('/guess', (req, res) => {
    req.session.isNaN = false;
   

    //gets number from post
    const raw = req.body.guess;
    const guess = parseInt(raw);
    //checks if input is debug
    if (raw === 'mode=debug') {
        req.session.debug = true;
    }
    else if (isNaN(guess) || guess === undefined || guess == '') { //checks if is number
            req.session.isNaN = true;
        }
    else {
        if (guess < req.session.secret) {
            req.session.guesses.push({guess: guess, status: 'low', message: 'too low'});
        }
        else if (guess > req.session.secret) {
            req.session.guesses.push({guess: guess, status: 'high', message: 'too high'});
        }
        else if (guess == req.session.secret) {
            req.session.state = true;
            req.session.guesses.push({guess: guess, status: 'correct', message: 'correct'});
        }
        req.session.count++;
    }
    req.session.save(() => {
        res.redirect(303, 'play');
    });
});