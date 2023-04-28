<html>
    <body>
        <p id="welcome"></p>

        <script>
            fetch("http://192.168.4.1/?get=username")
                .then(response => response.text())
                .then(data => {
                document.getElementById("welcome").textContent = "Welcome, " + data + "!";
                });
        </script>
    </body>
</html>
