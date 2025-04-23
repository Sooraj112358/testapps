Steps to Contribute

Clone the repository (if you haven’t already):
git clone https://github.com/soorajdevs/testapps.git
cd testapps

Checkout or create a feature branch from pulsar:
git checkout pulsar
git checkout -b feature/my-awesome-feature

Work on your changes, then commit and push:
git add .
git commit -m "Add: My awesome feature"
git push origin feature/my-awesome-feature

Open a Pull Request (PR):
Go to the GitHub page of this repository
Click "Compare & pull request"
Select main as the base branch and your feature branch as the compare
Add a meaningful title and description
Submit the PR for review

🔒 Branch Protection Rules
✅ Direct pushes to main are not allowed
✅ All changes must come via Pull Requests
✅ PRs may require:
✅ Code review/approval

🧼 Tip: Keep Your Branch Updated
Before submitting your PR, it's good practice to sync with the latest pulsar branch:
git checkout pulsar
git pull origin pulsar
git checkout feature/my-awesome-feature
git rebase pulsar

