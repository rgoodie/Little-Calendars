<?php

/*
Adapted from https://github.com/Goatella/PHP-Calendar/blob/master/cal.php. I in
turned, converted to a class, allowed input of a current date function, and added
other embellishments as needed such as date highlighting;
*/

Class PHPcal {

	// arrays that will be used later.
	private $ctmztns = array(),
		$directives = array(),
		$day_num = array(),
		$year,
		$month,
		$day,
		$day_count,
		$day_of_week,
		$days_in_month;


	public function __construct($processString) {
		$this->processString($processString);
	}

	/*
	Process incoming string from the Drupal input filter
	*/
	function processString($processString) {
		$incomingArray = explode("|", $processString);
		$this->year = array_shift($incomingArray);
		$this->month = array_shift($incomingArray);
		$this->day = 1;
		$this->directives = $incomingArray;

		unset($incomingArray);

		$this->processDirectives();


	}


	/*
	Creates an array keyed to the day of the month with link and necessary
	background color.
	*/
	function processDirectives() {

		//$this->ctmztns = array();

		// prime array elements with no data
		for ($i = 0; $i < 32; $i++) {
			$this->ctmztns[$i]['data'] = !TRUE;
		}


		foreach ($this->directives as $d) {

			$directive_parts = explode(',', $d);
			$link = array_shift($directive_parts);
			$bghx = array_shift($directive_parts);
			$days = $directive_parts;
			unset($directive_parts);

			// poplate necessary array elements with data
			foreach ($days as $indDay) {
				$this->ctmztns[$indDay]['link'] = $link;
				$this->ctmztns[$indDay]['bghx'] = $bghx;
				$this->ctmztns[$indDay]['data'] = TRUE;
			}
		}

		//$this->debug($this->ctmztns);

	}

	public function produceHtml() {
		// table cell width
		$tbl_cell_width = variable_get('soc_littlecalendars_tableCellWidth', 42);

		// init variable
		$output = '';


		//Here we generate the first day of the month
		$first_day = mktime(0, 0, 0, $this->month, 1, $this->year);

		//This gets us the month name
		$title = date('F', $first_day);

		//Here we find out what day of the week the first day of the month falls on
		$this->day_of_week = date('D', $first_day);

		//Once we know what day of the week it falls on, we know how many blank days occure before it. If the first day of the week is a Sunday then it would be zero
		switch ($this->day_of_week) {
			case "Sun":
				$blank = 0;
				break;
			case "Mon":
				$blank = 1;
				break;
			case "Tue":
				$blank = 2;
				break;
			case "Wed":
				$blank = 3;
				break;
			case "Thu":
				$blank = 4;
				break;
			case "Fri":
				$blank = 5;
				break;
			case "Sat":
				$blank = 6;
				break;
		}

		//We then determine how many days are in the current month
		$this->days_in_month = cal_days_in_month(0, $this->month, $this->year);

		//Here we start building the table heads
		$output .= "<table >";
		$output .= "<tr><th colspan=7> $title $this->year </th></tr>";
		$output .= "<tr><td width=$tbl_cell_width>S</td><td width=$tbl_cell_width>M</td><td width=$tbl_cell_width>T</td><td width=$tbl_cell_width>W</td><td width=$tbl_cell_width>T</td><td width=$tbl_cell_width>F</td><td width=$tbl_cell_width>S</td></tr>";

		//This counts the days in the week, up to 7
		$this->day_count = 1;
		$output .= "<tr>";

		//first we take care of those blank days
		while ($blank > 0) {
			$output .= "<td></td>";
			$blank = $blank - 1;
			$this->day_count++;
		}

		//sets the first day of the month to 1
		$this->day_num = 1;

		//count up the days, untill we've done all of them in the month
		while ($this->day_num <= $this->days_in_month) {


			// Check to see if the customization array has any information inside
			// of it. If so, let's use this.
			$bghx = ($this->ctmztns[$this->day_num]['data'] == TRUE) ? $this->ctmztns[$this->day_num]['bghx'] : '';

			// If there is background color information, set it in the td. Also use that as a class name.
			$class_name = str_replace('#', '', $bghx);
			$output .= t("<td style='background-color: @background_color;' class='@class_name'>", array(
				'@background_color' => $bghx,
				'@class_name' => $class_name,
			));


			if ($this->ctmztns[$this->day_num]['data'] == TRUE && $this->ctmztns[$this->day_num]['link'] != "none") {
				$output .= "<a href='" . $this->ctmztns[$this->day_num]['link'] . "'>";
				$output .= $this->day_num;
				$output .= "</a>";
			}
			else {
				$output .= $this->day_num;
			}
			$output .= "</td>";
			$this->day_num++;
			$this->day_count++;

			//Make sure we start a new row every week
			if ($this->day_count > 7) {
				$output .= "</tr><tr>";
				$this->day_count = 1;
			}
		}

		//Finaly we finish out the table with some blank details if needed
		while ($this->day_count > 1 && $this->day_count <= 7) {
			$output .= "<td> </td>";
			$this->day_count++;
		}

		$output .= "</tr></table>";
		return '<div class="' . variable_get('soc_littlecalendars_containerClass', 'minicalendar') . '">'
			. $output
			. '</div>';

	}


}
