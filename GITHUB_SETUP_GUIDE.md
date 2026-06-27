# GitHub Setup Guide — Pushing This Project from Scratch

This guide walks you through taking this folder (`d:\OOPFinalProject\Project1`) and pushing it to the GitHub repository you already created, assuming you have **never used Git or GitHub before**.

You already have Git installed (version 2.52.0), so we can skip installation.

---

## 0. Key Concepts (read this first)

- **Git** is a program on your computer that tracks changes to files over time. It works entirely offline, in a hidden `.git` folder.
- **GitHub** is a website that hosts a copy of your Git history online, so you can back it up, share it, or collaborate.
- A **repository** ("repo") is just a project folder that Git is tracking.
- **Commit** = a saved snapshot of your files at a point in time, with a message describing what changed.
- **Remote** = the online location (on GitHub) that your local repo is linked to. The default remote name is `origin`.
- **Push** = upload your local commits to the remote (GitHub).
- **Pull** = download commits from the remote into your local repo.
- **Branch** = an independent line of work. The default branch is usually called `main`.

The basic flow you'll repeat forever is:

```
edit files → git add → git commit → git push
```

---

## 1. Tell Git Who You Are (one-time setup)

Git stamps every commit with a name and email. Run these once (replace with your own info):

```bash
git config --global user.name "Your Name"
git config --global user.email "bismahjavedhussain@gmail.com"
```

Verify it worked:

```bash
git config --global --list
```

---

## 2. Create a `.gitignore` File

Your project folder contains files Git should **not** track:

- `.vs/` — Visual Studio's local cache/settings (machine-specific, regenerated automatically)
- `x64/` — compiled build output (binaries, object files — regenerated every build)

Tracking these bloats the repo and causes merge conflicts for no benefit. Create a file named `.gitignore` in `d:\OOPFinalProject\Project1` with this content:

```gitignore
# Visual Studio
.vs/
*.user
*.suo

# Build output
x64/
x86/
Debug/
Release/
*.obj
*.exe
*.pdb
*.ilk
*.idb
*.exp
*.lib
*.log
```

> If you already ran a build and Git tracks these files later by mistake, `.gitignore` only prevents *future* tracking — see step 7 for cleanup if needed.

---

## 3. Initialize Git in This Folder

Open a terminal **in `d:\OOPFinalProject\Project1`** and run:

```bash
git init
```

This creates a hidden `.git` folder — your project is now a Git repository (but nothing is saved yet).

Check what Git sees:

```bash
git status
```

You'll see a long list of "untracked files" — that's expected, nothing has been committed yet.

---

## 4. Stage and Commit Your Files

**Stage** files (mark them to be included in the next commit):

```bash
git add .
```

The `.` means "everything in this folder" (respecting `.gitignore`). Confirm what's staged:

```bash
git status
```

You should now see files listed in green ("Changes to be committed"), and `.vs/`/`x64/` should **not** appear at all (because `.gitignore` excludes them).

**Commit** the staged files with a message:

```bash
git commit -m "Initial commit: add game project source files"
```

This creates your first snapshot.

---

## 5. Connect Your Local Repo to GitHub

Go to your GitHub repository page (the one you already created) and copy its URL. It looks like:

- HTTPS: `https://github.com/your-username/your-repo-name.git`
- or SSH: `git@github.com:your-username/your-repo-name.git`

**If you're a beginner, use HTTPS** — it's simpler to set up (SSH requires extra key configuration).

Link your local repo to that GitHub repo as a "remote" named `origin`:

```bash
git remote add origin https://github.com/your-username/your-repo-name.git
```

Verify it was added:

```bash
git remote -v
```

---

## 6. Push to GitHub

First, make sure your local default branch is named `main` (modern GitHub convention):

```bash
git branch -M main
```

Now push, and set `origin/main` as the default upstream for future pushes:

```bash
git push -u origin main
```

### Authentication note (important for beginners)

GitHub no longer accepts your account password for `git push` over HTTPS. The first time you push, it will prompt you to authenticate — typically via:

- A browser popup (if using GitHub Desktop's credential manager or Git Credential Manager, which usually comes bundled with Git for Windows) — just sign in when prompted.
- Or a **Personal Access Token (PAT)** used in place of a password, if a browser prompt doesn't appear. You'd generate one at GitHub → Settings → Developer settings → Personal access tokens.

If a browser window pops up asking you to authorize Git, just log in and approve it — that's the easiest path.

---

## 7. Verify

Refresh your GitHub repository page in the browser. You should now see all your project files there.

If `.vs/` or `x64/` accidentally got pushed (e.g., you committed before adding `.gitignore`), remove them from tracking without deleting them locally:

```bash
git rm -r --cached .vs x64
git commit -m "Remove IDE/build folders from tracking"
git push
```

---

## 8. Your Day-to-Day Workflow Going Forward

Every time you make changes and want to save/back them up to GitHub:

```bash
git status              # see what changed
git add .                # stage changes
git commit -m "Describe what you changed"
git push                 # upload to GitHub
```

A few more useful commands as you grow:

| Command | What it does |
|---|---|
| `git log` | Shows commit history |
| `git diff` | Shows uncommitted changes line-by-line |
| `git pull` | Downloads latest changes from GitHub |
| `git checkout -b feature-name` | Creates and switches to a new branch |
| `git branch` | Lists branches |

---

## Quick Reference: Full Sequence for This Project

```bash
# one-time identity setup
git config --global user.name "Your Name"
git config --global user.email "bismahjavedhussain@gmail.com"

# from inside d:\OOPFinalProject\Project1
git init
# (create .gitignore as shown in step 2)
git add .
git commit -m "Initial commit: add game project source files"
git remote add origin https://github.com/your-username/your-repo-name.git
git branch -M main
git push -u origin main
```

After this first push, all future updates are just:

```bash
git add .
git commit -m "your message"
git push
```
