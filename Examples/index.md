---
layout: page
title: Examples
---

# Click to download

<ul>
{% for file in site.static_files %}
    {% if file.path contains 'Examples' %}
        {% unless file.name == "index.html" %}
            <li><a href="{{ file.path | prepend: site.baseurl }}">{{ file.name }}</a></li>
        {% endunless %}
    {% endif %}
{% endfor %}
</ul>
