---
layout: page
title: Examples
---

# Click to download

<ul>
{% for file in site.static_files %}
    {% if file.path contains 'examples' %}
       <li><a href="{{ file.path | prepend: site.baseurl }}">{{ file.name }}</a></li>
    {% endif %}
{% endfor %}
</ul>
