---
layout: page
title: Examples
---

# Click to download

<ul>
{% for file in site.static_files %}
    {% if file.path contains 'Examples' %}
       <li><a href="{{ file.path | prepend: site.url }}">{{ file.name }}</a></li>
    {% endif %}
{% endfor %}
</ul>
