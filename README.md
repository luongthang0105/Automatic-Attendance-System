# Automatic-Attendance-System
This is another project I've done in my high school. I've done several Arduino projects, but this one has been the most difficult and complex. <br>
The projects' name is Automatic Attendance System. we will assigned attendees' names into NFC tag and use RFID-RC522 Arduino module to read the NFC tag. <br>

In brief, we have two phases for this project. <br>
The first phase is **writing** information of attendee (e.g. names).
<br>
Demo for **writing** phase: <br>
<a href="http://www.youtube.com/watch?feature=player_embedded&v=6kkPixtEpC0
" target="_blank"><img src="http://img.youtube.com/vi/6kkPixtEpC0/0.jpg" 
alt="demo write.ino" width="240" height="180" border="10" /></a>
<br>

The latter is **reading** from the NFC tag and writing the information down on a seperate excel file.
Demo for **reading** phase: <br>
<a href="http://www.youtube.com/watch?feature=player_embedded&v=BQvGl_s3MQY
" target="_blank"><img src="http://img.youtube.com/vi/BQvGl_s3MQY/0.jpg" 
alt="demo read.ino" width="240" height="180" border="10" /></a>
<br> The information from reading the tags will be written onto an Excel file using a third party application called **PLX-DAQ**.
<br> The first sheet of the excel file will show users who and when did someone attend. 
<br> The second sheet shows the total number of people, number of attendees, and number of absent attendees.

