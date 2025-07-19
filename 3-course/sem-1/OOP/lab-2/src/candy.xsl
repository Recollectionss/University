<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="xml" indent="yes"/>

    <xsl:key name="candiesByType" match="candy" use="type" />

    <xsl:template match="/root">
        <root>
            <xsl:for-each select="candy[generate-id() = generate-id(key('candiesByType', type)[1])]">
                <xsl:element name="{type}">
                        <xsl:for-each select="key('candiesByType', type)">
                            <candy>
                                <name><xsl:value-of select="name"/></name>
                                <energy><xsl:value-of select="energy"/></energy>
                                <ingredients>
                                    <water><xsl:value-of select="ingredients/water"/></water>
                                    <sugar><xsl:value-of select="ingredients/sugar"/></sugar>
                                    <fructose><xsl:value-of select="ingredients/fructose"/></fructose>
                                    <chocolateType><xsl:value-of select="ingredients/chocolateType"/></chocolateType>
                                    <vanillin><xsl:value-of select="ingredients/vanillin"/></vanillin>
                                </ingredients>
                                <value>
                                    <proteins><xsl:value-of select="value/proteins"/></proteins>
                                    <fats><xsl:value-of select="value/fats"/></fats>
                                    <carbohydrates><xsl:value-of select="value/carbohydrates"/></carbohydrates>
                                </value>
                                <production><xsl:value-of select="production"/></production>
                            </candy>
                        </xsl:for-each>
                </xsl:element>
            </xsl:for-each>
        </root>
    </xsl:template>

</xsl:stylesheet>
