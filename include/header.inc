<?php
/* $Id$ */

$css_files = array(
    '/styles/material.indigo-red.min.css',
    '/styles/theme.css',
    '/styles/highlight.css',
);

if (isset($config['css'])) {
    $css_files = array_merge($css_files, (array) $config['css']);
}
if (isset($config["css_overwrite"])) {
    $css_files = $config["css_overwrite"];
}

foreach($css_files as $filename) {
    // files that do not start with / are assumed to be located in the /styles
    // directory
    if ($filename[0] !== '/') {
        $filename = "/styles/$filename";
    }
    $path = dirname(__DIR__) . $filename;
    $CSS[$filename] = @filemtime($path);
}


if (isset($shortname) && $shortname) {
    header("Link: <$shorturl>; rel=shorturl");
}

if ($config["cache"]) {
    if (is_numeric($config["cache"])) {
        $timestamp = $config["cache"];
    } else {
        $timestamp = filemtime($_SERVER["DOCUMENT_ROOT"] . "/" .$_SERVER["BASE_PAGE"]);
    }
    $tsstring = gmdate("D, d M Y H:i:s ", $timestamp) . "GMT";

    if (isset($_SERVER["HTTP_IF_MODIFIED_SINCE"]) && $_SERVER["HTTP_IF_MODIFIED_SINCE"] == $tsstring) {
        header("HTTP/1.1 304 Not Modified");
        exit;
    }
    header("Last-Modified: " . $tsstring);
}
if (!isset($config["languages"])) {
    $config["languages"] = array();
}

?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?= $lang?>">
<head>

  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">

  <title>PHP: <?= $title ?></title>

 <link rel="shortcut icon" href="<?= $MYSITE ?>favicon.ico">
 <link rel="search" type="application/opensearchdescription+xml" href="http://php.net/phpnetimprovedsearch.src" title="Add PHP.net search">
 <link rel="alternate" type="application/atom+xml" href="<?= $MYSITE ?>releases/feed.php" title="PHP Release feed">
 <link rel="alternate" type="application/atom+xml" href="<?= $MYSITE ?>feed.atom" title="PHP: Hypertext Preprocessor">

<?php if (isset($_SERVER['BASE_PAGE'])): ?>
 <link rel="canonical" href="http://php.net/<?= $_SERVER['BASE_PAGE']?>">
<?php if ($shortname): ?>
 <link rel="shortlink" href="<?= $shorturl ?>">
 <link rel="alternate" href="<?= $shorturl ?>" hreflang="x-default">
<?php endif ?>
<?php endif ?>

<?php foreach($config["meta-navigation"] as $rel => $page): ?>
 <link rel="<?= $rel ?>" href="<?= $MYSITE ?><?= $page ?>">
<?php endforeach ?>

<?php foreach($config["languages"] as $code): ?>
 <link rel="alternate" href="<?= $MYSITE ?>manual/<?= $code?>/<?= $config["thispage"] ?>" hreflang="<?= $code?>">
<?php endforeach ?>

	<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
<?php foreach($CSS as $filename => $modified): ?>
<link rel="stylesheet" type="text/css" href="<?= $MYSITE ?>cached.php?t=<?= $modified?>&amp;f=<?= $filename?>" media="screen">
<?php endforeach ?>

<?php if (!empty($_SERVER["BASE_HREF"])): ?>
 <base href="<?= $_SERVER["BASE_HREF"] ?>">
<?php endif ?>

</head>
<body class="<?= $curr; ?> <?= $classes; ?>">

<div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
	<header class="mdl-layout__header">
		<div class="mdl-layout__header-row">
			<a class="mdl-layout-title" href="/"><img src="/images/logos/php-logo.svg" width="48" height="24" alt="php"></a>
			<!-- Navigation. We hide it in small screens. -->
			<nav class="mdl-navigation mdl-layout--large-screen-only">
				<a class="mdl-navigation__link <?= $curr == "downloads" ? "active" : ""?>" href="/downloads">Downloads</a>
				<a class="mdl-navigation__link <?= $curr == "docs" ? "active" : ""?>" href="/docs.php">Documentation</a>
				<a class="mdl-navigation__link <?= $curr == "community" ? "active" : ""?>" href="/get-involved">Get Involved</a>
				<a class="mdl-navigation__link <?= $curr == "help" ? "active" : ""?>" href="/support">Help</a>
			</nav>
			<div class="mdl-layout-spacer"></div>
			<div class="mdl-textfield mdl-js-textfield mdl-textfield--expandable mdl-textfield--floating-label mdl-textfield--align-right">
				<label class="mdl-button mdl-js-button mdl-button--icon" for="fixed-header-drawer-exp">
					<i class="material-icons">search</i>
				</label>
				<form class="mdl-textfield__expandable-holder" action="/search.php">
					<input class="mdl-textfield__input" type="text" name="sample" id="fixed-header-drawer-exp">
				</form>
			</div>
		</div>
	</header>
	<div class="mdl-layout__drawer mdl-layout--small-screen-only">
		<span class="mdl-layout-title">Title</span>
		<nav class="mdl-navigation">
			<a class="mdl-navigation__link <?= $curr == "downloads" ? "active" : ""?>" href="/downloads">Downloads</a>
			<a class="mdl-navigation__link <?= $curr == "docs" ? "active" : ""?>" href="/docs.php">Documentation</a>
			<a class="mdl-navigation__link <?= $curr == "community" ? "active" : ""?>" href="/get-involved">Get Involved</a>
			<a class="mdl-navigation__link <?= $curr == "help" ? "active" : ""?>" href="/support">Help</a>
		</nav>
	</div>

	<main class="mdl-layout__content">
		<div class="page-content">

<nav id="head-nav" class="navbar navbar-fixed-top">
    <a href="/" class="brand"></a>
</nav>
<div id="flash-message"></div>
<?php if (!empty($config["headsup"])): ?>
<div class="headsup"><?= $config["headsup"]?></div>
<?php endif ?>
<nav id="trick"><div><?php doc_toc("en") ?></div></nav>
<div id="goto">
    <div class="search">
         <div class="text"></div>
         <div class="results"><ul></ul></div>
   </div>
</div>

<?php if (!empty($config['breadcrumbs'])): ?>
  <div id="breadcrumbs">
    <div id="breadcrumbs-inner">
    <?php if (isset($config['next'])): ?>
      <div class="next">
        <a href="<?= $config['next'][0]; ?>">
          <?= $config['next'][1]; ?> &raquo;
        </a>
      </div>
    <?php endif; ?>
    <?php if (isset($config['prev'])): ?>
      <div class="prev">
        <a href="<?= $config['prev'][0]; ?>">
          &laquo; <?= $config['prev'][1]; ?>
        </a>
      </div>
    <?php endif; ?>
      <ul>
      <?php
          $breadcrumbs = $config['breadcrumbs'];
          $last = array_pop($breadcrumbs);
          foreach ($breadcrumbs as $crumb) {
              echo "      <li><a href='{$crumb['link']}'>{$crumb['title']}</a></li>";
          }
          echo "      <li><a href='{$last['link']}'>{$last['title']}</a></li>";

      ?>
      </ul>
    </div>
  </div>
<?php endif; ?>


<?php if (!empty($config['intro'])):?>
<div id="intro" class="mdl-grid">
	<?= $config['intro'];?>
</div>
<?php endif;?>


