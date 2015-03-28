# AmIAway

*AmIAway* is a simple UI-less activity monitor for Windows.

## Project Structure

*AmIAway* consists of two parts: `ActivityMonitor` class which monitors the user’s activity and inactivity periods using Windows API, and loggers that handle user activity changes in a specific way.

At the moment if March 2015, two loggers are present:

 - `ActivityLogger` class which prints user activity changes to (invisible) console,
 - and `ActivityServer` class which sends user activity changes to an url specified by the class settings.

## License

*AmIAway* is licensed under MIT license.