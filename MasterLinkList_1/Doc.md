# Converting a Word Document to Markdown in Two Moves

## The Problem

A lot of important government documents are created and saved in Microsoft Word (*.docx). But Microsoft Word is a proprietary format, and it's not really useful for presenting documents on the web. So, I wanted to find a way to convert a .docx file into markdown.

## The Solution

As it turns out, there are several open-source tools that allow for conversion between file types. [Pandoc](johnmacfarlane.net/pandoc/) is one of them, and it's powerful. In fact, pandoc's website says "If you need to convert files from one markup format into another, pandoc is your swiss-army knife." But, although pandoc can convert from markdown into .docx, it doesn't work in the other direction.

Then I found [unoconv](http://dag.wieers.com/home-made/unoconv/). This little tool takes advantage of OpenOffice's ability to convert a Word document into a bunch of different formats. But, unoconv too has a bit of a downside. Specifically, unoconv tries to keep a lot of the formatting that Word has embedded in a document. The output is, well, messy.

But, by using unconv and pandoc in combination, you can get a pretty clean output. And, the best part is that it retains footnotes and other key syntax (italics, etc.)

## Example

Say you have the Council Rules in a Word Document named "test.docx." [(For a real-life example, visit http://github.com/vzvenyach/Council_Rules/).](http://github.com/vzvenyach/Council_Rules/) Now, you run the following at the command line:

    unoconv -f html test.docx
    pandoc -f html -t markdown -o test.md test.html

Out is a beautiful markdown file. Admittedly, there's a bit of junk at the top with the Table of Contents. I deleted this when I rendered it nicely with strapdown.js. [In the end, here's my nicely rendered version of the Rules.](http://vzvenyach.github.io/Council_Rules/Rules.html)