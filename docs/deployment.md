# Deployment Guide

This document describes how the Novus documentation is deployed to GitHub Pages.

## Automated Deployment (Recommended)

The documentation is automatically built and deployed whenever changes are pushed to the `main` or `master` branch. This is handled by a GitHub Actions workflow located at `.github/workflows/deploy-docs.yml`.

### How it works:
1.  **Triggers**: Pushes to `main`/`master` that include changes in `docs/`, `mkdocs.yml`, `README.md`, or `CONTRIBUTING.md`.
2.  **Environment**: Uses `ubuntu-latest` with Python 3.x.
3.  **Dependencies**: Installs `mkdocs-material`.
4.  **Deployment**: Runs `mkdocs gh-deploy --force`, which builds the site and pushes the contents of the `site/` directory to the `gh-pages` branch.

## Manual Deployment

If you need to deploy manually from your local machine:

1.  **Install MkDocs and the Material theme**:
    ```bash
    pip install mkdocs-material
    ```

2.  **Prepare the docs directory**:
    Ensure `docs/index.md` and `docs/contributing.md` are up to date with `README.md` and `CONTRIBUTING.md`.

3.  **Deploy**:
    ```bash
    mkdocs gh-deploy
    ```
    *Note: This requires write access to the repository.*

## GitHub Pages Configuration

1.  In your GitHub repository, go to **Settings** > **Pages**.
2.  Under **Build and deployment**, ensure **Source** is set to "Deploy from a branch".
3.  Set the **Branch** to `gh-pages` and the folder to `/(root)`.
4.  Once the workflow runs, your site will be available at `https://<username>.github.io/novus/`.
