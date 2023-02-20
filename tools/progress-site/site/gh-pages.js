var ghpages = require('gh-pages');

ghpages.publish(
    'public', // path to public directory
    () => {
        console.log('Deploy Complete!')
    }
)