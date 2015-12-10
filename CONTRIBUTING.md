# How to contribute

We currently have three distinct development stages.
* Dev: for integrating features under development
* Testing: for testing complete features
* Master: for tested features

If your changes are significant then make a new branch that is named after the Jira issue.

## Making Changes

* Create a topic branch from where you want to base your work.
  * This is usually the master branch.
  * To quickly create a topic branch based on master; `git checkout -b
    fix/master/my_contribution master`. Please avoid working directly on the
    `master` branch.
* Make commits of logical units.
* Check for unnecessary whitespace with `git diff --check` before committing.
* Make sure your commit messages are accurate and coherent.
