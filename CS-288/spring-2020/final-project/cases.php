<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Covid-19 Tracker</title>
  <link rel="stylesheet" href="index.css">
</head>
<body>
    <h1 style="text-align: center">United States Covid 19 Tracker</h1>

    <table align="center" border="1">
    <?php
    $cnx = new mysqli('localhost', 'USERNAME', 'PASSWORD', 'cs_288_covid');

    if ($cnx->connect_error) {
        die('Connection failed: ' . $cnx->connect_error);
    }

    echo '<tr class="header" style="text-align: center;">';

    $validCols = array('us_state', 'confirmed_cases', 'new_cases', 'confirmed_deaths', 'new_deaths');

    function renderHeaderItem($col) {
        $innerText = '';

        switch ($col) {
            case 'us_state':
                $innerText = 'State';
                break;
            case 'confirmed_cases':
                $innerText = 'Confirmed Cases';
                break;
            case 'new_cases':
                $innerText = 'New Cases';
                break;
            case 'confirmed_deaths':
                $innerText = 'Confirmed Deaths';
                break;
            case 'new_deaths':
                $innerText = 'New Deaths';
                break;
            default:
                break;
        }

        if (strcmp($_SERVER['QUERY_STRING'], 'orderBy=' . $col . '&sortBy=ASC') == 0) {
            echo '<td><a href="?orderBy=' . $col . '&sortBy=DESC">' . $innerText . '</a></td>';
        } else {
            echo '<td><a href="?orderBy=' . $col . '&sortBy=ASC">' . $innerText . '</a></td>';
        }
    }

    foreach ($validCols as $headerCol) {
        renderHeaderItem($headerCol);
    }

    echo '</tr>';

    $totalConfirmedCases = 0;
    $totalNewCases = 0;
    $totalConfirmedDeaths = 0;
    $totalNewDeaths = 0;

    $orderBy = isset($_GET['orderBy']) && in_array($_GET['orderBy'], $validCols) ? $_GET['orderBy'] : 'confirmed_cases';

    $sortyBy = (isset($_GET['sortBy']) && $_GET['sortBy'] == 'ASC' || $_GET['sortBy'] == 'DESC') ? $_GET['sortBy'] : 'DESC';

    // default sort is confirmed_cases DESC
    $query = "SELECT * FROM covid_cases ORDER BY $orderBy $sortyBy";
    $cursor = $cnx->query($query);

    while ($row = $cursor->fetch_assoc()) {
        echo '<tr>';
        $i = 0;
        foreach($row as $key => $value) {
            echo '<td>' . $value . '</td>';

            switch ($i) {
                case 1:
                    $totalConfirmedCases += $value;
                    break;
                case 2:
                    $totalNewCases += $value;
                    break;
                case 3:
                    $totalConfirmedDeaths += $value;
                    break;
                case 4:
                     $totalNewDeaths += $value;
                    break;
                default:
                    break;
            }

            $i++;
        }
        echo '</tr>';
    }

    echo '<ul style="text-align: center">';
    echo '<p>Total Confirmed Cases: ' . $totalConfirmedCases .  ' </p>';
    echo '<p>Total New Cases: ' . $totalNewCases .  ' </p>';
    echo '<p>Total Confirmed Deaths: ' . $totalConfirmedDeaths .  ' </p>';
    echo '<p>Total New Deaths: ' . $totalNewDeaths .  ' </p>';
    echo '</ul>';

    $cnx->close();
    ?>
    </table>

    <script>
    var queryParams = window.location.search.trim();

    if (!queryParams) {
        window.location.href = window.location.pathname + "?orderBy=confirmed_cases&sortBy=DESC"
    }
    </script>
</body>
</html>
