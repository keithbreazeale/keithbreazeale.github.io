# Welcome
This ePortfolio serves as a comprehensive amalgamation of the knowledge and proficiencies cultivated during my tenure in the Computer Science program at Southern New Hampshire University (SNHU). It encapsulates my progressive journey within the program, showcasing achievements that have earned me prestigious accolades for exceptional outcomes. Meticulously crafted, this ePortfolio is a testament to my professional growth, manifesting in eloquent written content and visually compelling communication. Its seamless cohesion, technical prowess, and tailored approach aptly cater to specific technical audiences and contexts, exemplifying my competencies and adaptability.

# Table of Contents
* [Code Reviews](#code-reviews)
* [Software Design and Engineering / Database Application](#software-design-and-engineering-/-database-application)
* [Algorithms and Data Structures Application](#algorithms-and-data-structures-application)

# Code Reviews
Below are the code reviews that I have completed based on specific categories.

## Software Design and Engineering and Database Category
The artifact that I am choosing for both the Software Engineering/Design and Database categories is the “Grazioso Salvare Animal Finder Application. This application has a Python front end and utilizes MongoDB (NoSQL) for it’s database. This artifact was developed in the CS 340: Client/Server Development course at SNHU. 
I was tasked with creating a web application that interfaces with existing animal shelter databases. The goal is to identify and categorize dogs suitable for various rescue scenarios like water rescue, mountain/wilderness rescue, disaster recovery, and scent tracking for specific individuals. This application streamlines interaction with individual dog profiles sourced from a MongoDB database.
The user interface will be a user-friendly and intuitive dashboard accessible to clients. This approach leverages the Model-View-Controller (MVC) software design pattern, providing a structured and organized framework. Additionally, the application will incorporate a RESTful protocol, extending the capabilities of the HTTP protocol to offer an application programming interface (API) for seamless communication between components. This combination of technologies aims to enhance usability, minimize errors, and optimize training time.
The video version of the Code Review can be found [here.](https://www.youtube.com/watch?v=I1r4QC94PJw)

## Algorithms and Data Structures
The artifact that I am choosing for the Algorithms and Data Structures category is the Binary Search Tree Algorithm. This artifact is a data structure capable of storing bid information and enabling rapid retrieval of a specific ID number using a binary search tree algorithm. This artifact was developed in the CS 260: Data Structures and Algorithms course at SNHU.
This code defines a binary search tree class (BinarySearchTree) and its associated methods to manage a collection of bids. It also includes utility functions for loading data from a CSV file, converting strings to doubles, and displaying bid information. The program uses a simple command-line interface to interact with the binary search tree.
The video version of the Code Review can be found [here.](https://www.youtube.com/watch?v=by6N7GbmcWM)

# Software Design and Engineering / Database Application
As mentioned in the Software Engineering Design and Database Category Code Review, the application that was chosen was the "Grazioso Salvare Animal Finder" Application. This application has a Python front end and utilizes MongoDB (NoSQL) for it’s database. This artifact was conceptualized, designed, and built as part of the CS 340 Client/Server Development course at SNHU. The objective of the web application is to create a user-friendly interface that interfaces with an existing animal shelter database. Its purpose is to identify and categorize dogs available for various rescue training programs.  Developed using Python and the Dash framework, the application integrates with MongoDB, a non-relational database, using the PyMongo driver. It's designed to operate within Jupyter Notebook for testing and through a computer terminal with an internet browser. The app's functionalities include importing a CSV file of shelter dogs into MongoDB, incorporating necessary dependencies such as Python libraries, PyMongo, and the Dash framework. It also includes a Python source code and CRUD module to manipulate the imported data within MongoDB.

This artifact constitutes a multi-tier application employing the Model View Controller (MVC) architecture and RESTful protocol design, extending the HTTP protocol to offer an API. The MVC pattern emphasizes a clear separation of concerns: the model handles data management, the view determines the user interface using the Dash framework, and the controller retrieves and modifies data via the PyMongo driver. 
Each record in the MongoDB database is a BSON document, retrieved in a JSON format by the web app. Execution of the main app file in the computer terminal prompts the opening of a new tab in the internet browser, loading the client-facing web application dashboard. This dashboard mirrors the following screen:

<div style="text-align: center;">
    <img src="CS 340/CS-340 Dashboard.png" width="800px" title="Web App Client/Database Screenshot" />
    <p><em>Grasiozo Salvare Search Web App Client/Database Dashboard Screenshot</em></p>
</div>

The focus of the artifact enhancements was on transitioning the web application from the Apporto Virtual Lab, a Linux-based remote desktop platform, to a Windows environment. Following the initial development in the Apporto Virtual Lab, I meticulously redesigned the software to cater to user requirements within a structured framework. Relying on the provided documentation as a guide, I meticulously replicated the web application environment in a Windows terminal, continuously updating and refining the documentation to reflect the steps taken in this recreation process. There was also some issues with the geolocational chart rendering that I was able to resolve.

The setup and execution of the web application posed considerable challenges. However, this experience showcased my proficiency in employing well-established and inventive techniques, tools, and skills within computing practices. Before delving into the web application documentation, I adeptly navigated the setup procedures for Python and MongoDB. Furthermore, adapting the web app's source code functionality to accommodate changes in the PyMongo driver version and an upgraded MongoDB platform underscored my ability to implement computer solutions that not only deliver value but also align with industry-specific objectives.

Original Application code can be found [here.](https://github.com/keithbreazeale/keithbreazeale.github.io/tree/main/CS%20340/Old%20Application)
Enhanced Application code can be found [here.](https://github.com/keithbreazeale/keithbreazeale.github.io/tree/main/CS%20340/Application)

# Algorithms and Data Structures Application
As mentioned in the Algorithms and Data Structures Code review, the application that was chosen was the "Binary Search Tree" Application. This application is written in C++. This artifact was conceptualized, designed, and built as part of the CS 260: Data Structures and Algorithms course at SNHU. The objective of this application was to create a small, efficient program for loading bid information and then allowing the user to search through the bids via a terminal. 

<div style="text-align: center;">
    <img src="CS 260/CS 260 Interface.png" width="800px" title="Bid Information Search Tool based on the Binary Search Tree Algorithm Screenshot" />
    <p><em>Bid Information Search Tool based on the Binary Search Tree Algorithm Screenshot</em></p>
</div>

The focus of the artifact enhancements was to enable the ability to list all bids by dollar amount as well as the ability to find all bids by a dollar amount within a specific range. While making the enhancements, I was able to put my developer hat on and look at things from that perspective which allowed me to improve the structure of the code not only from something as simple as comments but to the overall functionality of the application. I also was able to put my end user hat on, to review the existing code and confirm if there was anything that didn’t work as intended. 

Original Application code can be found [here.](https://github.com/keithbreazeale/keithbreazeale.github.io/tree/main/CS%20260/Old%20Application)
Enhanced Application code can be found [here.](https://github.com/keithbreazeale/keithbreazeale.github.io/tree/main/CS%20260/Application)
