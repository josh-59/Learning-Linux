#! /usr/bin/ruby

# An automated script to update and synchronize navigation amongst pages
# To-Do:
#     Finish implementation so script builds all webpages
#     Generalize implementation by separating "Search file for instruction"
#

# Locate all directories that are candidates for being built
directories = []

Dir.entries(".").each { |entry|
  if( entry[0] == '.') then
    next;
  end

  if( File.directory?(entry) ) then
    directories.append(entry)
  end

}

# Get all directories containing "content"
active_pages = []
directories.each() { |dir|
  if( Dir.entries(dir).include? "content" ) then
    puts("Found page #{dir}")
    active_pages.append(dir)
  end
}

# Sort pages
active_pages.sort

# Get href, short_title, long_title for each active page
href  = {}
short_title = {}
long_title = {}

active_pages.each { |page|
  href[page] = page
  comment = false
  File.readlines(page + "/content").each { |line|
    line.strip!

    if( line.start_with?("<!--")) then
      comment = true
    elsif( line.start_with?("-->")) then
      comment = false
    end

    if( comment and line.start_with?("short_title:")) then
      short_title[page] = line.split("short_title:")[1].strip!
    elsif( comment and line.start_with?("long_title:")) then
      long_title[page] = line.split("long_title:")[1].strip!
    end
  }
  if !short_title[page] then
    $stderr.puts "\e1;31mWarning: Did not capture short title for page #{page}\e[m"
  end

  if !long_title[page] then
    $stderr.puts "\e1;31mWarning: Did not capture long title for page #{page}\e[m"
  end
}


include = {}

# Build nav_home
nav_home = <<HERE
<div id="nav_home" class="nav">
\t<ul>
\t\t<li> <a class="active" href=".">Home</a> </li>
HERE

active_pages.each { |page|
  nav_home = nav_home + "\t\t<li> <a href=\"#{href[page]}\">#{long_title[page]}</a> </li>\n"
}

nav_home = nav_home + <<HERE
\t</ul>
</div>
HERE

include["nav_home"] = nav_home

# Build homepage; ensure ./content exists before deleting index.html
file_name = "homepage"
puts "Building page [#{file_name}]"
cur_content = File.open("./content", "r")
File.delete("./index.html")
cur_page = File.open("./index.html", "w")

comment = false

cur_content.readlines.each { |line|
  if line.start_with?("<!--") then
    comment = true
  elsif line.start_with?("-->") then
    comment = false
    puts "\tRemoving comment: #{line}"
    next
  end

  if( comment ) then
    line.strip!
    puts "\tRemoving comment: #{line}"
    if line.start_with?("include:") then
      i = line.split("include:")[1].strip!
      if( !include[i] ) then
        $stderr.puts "\t\e[1;31mWarning: Unknown include reference \"#{i}\" in [#{file_name}]\e[m"
      else
        cur_page.puts include[i]
      end
    end
  else
    cur_page.puts line
  end
}
