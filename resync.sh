safe_commit() {
    git diff --quiet && git diff --staged --quiet || git commit -m "$1"
}

git add --all
safe_commit 'Automatically commit working tree changes'
git fetch https://github.com/doldecomp/melee.git master
git reset --soft FETCH_HEAD
safe_commit 'Automatically merge with doldecomp/master'
git push --force
