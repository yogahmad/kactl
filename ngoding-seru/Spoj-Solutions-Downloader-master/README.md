# Spoj-Solutions-Downloader
This python script downloads all the solutions for solved problem on spoj for a user. 

<b>Platform:</b> Linux with python 2.7

<b>Installing Requirements</b>
<ul>
<li>RoboBrowser: sudo pip install robobrowser</li>
<li>The other option is to create a virtualenv and then install all the requirements given in requirements.txt using pip -r install requirements.txt</li>
</ul>

<b>Running the script:</b> python spoj.py

Enter your spoj username and password when asked. Then, it will download all solutions in a folder "spoj_solutions" in the same directory where the script is.

<b>Note:</b> The script only downloads the last submitted solution for all the questions even if that solution is not an accepted one.
