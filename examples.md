---
layout: page
title: Examples
---

# Examples

<ul>
{% for file in site.static_files %}
    {% if file.path contains 'Examples' %}
       <li><a href="{{ file.path | prepend: site.baseurl | prepend: site.url }}">{{ file.name }}</a></li>
    {% endif %}
{% endfor %}
</ul>
