# Using GradleW

Make sure you have Java installed:
```
# Update package repos
sudo apt update 

# Install java
sudo apt install openjdk-8-jdk 
```

Get the example code zip off of the release page, and unzip it into a new directory:
```
mkdir Projects/GradleTest
cd Projects/GradleTest
wget https://github.com/wpilibsuite/GradleRIO/releases/download/v2019.2.1/cpp.zip
unzip cpp.zip 
```

Allow GradleW to download and set itself up while building:
```
# Install the RoboRio Toolchain
./gradlew installRoboRioToolchain

# Build the project
./gradlew build
```

Set the team number:
```
$EDITOR .wpilib/wpilib_preferences.json
 --
{
  "enableCppIntellisense": true,
  "currentLanguage": "cpp",
  "projectYear": "Beta2019",
  "teamNumber": 955
}
```

Make sure that gradlew can find the RIO:
```
# Find the RIO
./gradlew discoverRoborio
```

Deploy to the robot:
```
./gradlew deploy
```
