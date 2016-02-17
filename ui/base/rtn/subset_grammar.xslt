<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fn="http://www.w3.org/2005/xpath-functions" xmlns:xdt="http://www.w3.org/2005/xpath-datatypes" xmlns:xs="http://www.w3.org/2001/XMLSchema">
	<xsl:output version="1.0" method="html" indent="no" encoding="UTF-8"/>
	<xsl:param name="SV_OutputFormat" select="'HTML'"/>
	<xsl:variable name="XML" select="/"/>
	<xsl:template match="/">
		<xsl:for-each select="$XML">
			<xsl:for-each select="subset">
				<subset xmlns="http://www.jedox.com/palo/SubsetXML">
					<xsl:variable name="ssId" select="id/@value"/>
					<xsl:if test="$ssId != ''">
						<xsl:attribute name="id"><xsl:value-of select="$ssId"/></xsl:attribute>
					</xsl:if>
					<xsl:variable name="ssSdId" select="sourceDimensionId/@value"/>
					<xsl:if test="$ssSdId != ''">
						<xsl:attribute name="sourceDimensionId"><xsl:value-of select="$ssSdId"/></xsl:attribute>
					</xsl:if>
					<xsl:for-each select="indent">
						<indent>
							<xsl:for-each select="param">
								<parameter>
									<xsl:value-of select="@value"/>
								</parameter>
							</xsl:for-each>
							<xsl:for-each select="value">
								<value>
									<xsl:value-of select="@value"/>
								</value>
							</xsl:for-each>
						</indent>
					</xsl:for-each>
					<xsl:if test="alias1 or alias2">
						<alias_filter>
							<xsl:for-each select="alias1">
								<alias1>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</alias1>
							</xsl:for-each>
							<xsl:for-each select="alias2">
								<alias2>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</alias2>
							</xsl:for-each>
						</alias_filter>
					</xsl:if>

					<!-- HIER -->
					<xsl:for-each select="hier">
						<hierarchical_filter>
							<!-- Filter elements hierarchically -->
							<xsl:for-each select="element">
								<element>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</element>
							</xsl:for-each>
							<xsl:for-each select="above">
								<above>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</above>
							</xsl:for-each>
							<xsl:for-each select="exclusive">
								<exclusive>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</exclusive>
							</xsl:for-each>
							<xsl:for-each select="hide">
								<hide>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</hide>
							</xsl:for-each>
							<xsl:for-each select="level_start">
								<level_start>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</level_start>
							</xsl:for-each>
							<xsl:for-each select="level_end">
								<level_end>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</level_end>
							</xsl:for-each>
							<!-- Cyclic list -->
							<xsl:for-each select="revolve_element">
								<revolve_element>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</revolve_element>
							</xsl:for-each>
							<xsl:for-each select="revolve_count">
								<revolve_count>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</revolve_count>
							</xsl:for-each>
							<xsl:for-each select="revolve_add">
								<revolve_add>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</revolve_add>
							</xsl:for-each>
						</hierarchical_filter>
					</xsl:for-each>

					<!-- TEXT -->
					<xsl:for-each select="text">
						<text_filter>
							<xsl:for-each select="regexes">
								<regexes>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:for-each select="elem">
												<expression>
													<xsl:value-of select="@value"/>
												</expression>
											</xsl:for-each>
										</value>
									</xsl:for-each>
								</regexes>
							</xsl:for-each>
							<xsl:for-each select="extended">
								<extended>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</extended>
							</xsl:for-each>
						</text_filter>
					</xsl:for-each>

					<!-- PICKLIST -->
					<xsl:for-each select="pick">
						<picklist_filter>
							<manual_definition>
								<xsl:for-each select="elems">
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:for-each select="elem">
												<pick_elem>
													<xsl:value-of select="@value"/>
												</pick_elem>
											</xsl:for-each>
										</value>
									</xsl:for-each>
								</xsl:for-each>
							</manual_definition>
							<xsl:for-each select="pick_type">
								<pick_type>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</pick_type>
							</xsl:for-each>
						</picklist_filter>
					</xsl:for-each>

					<!-- ATTRIBUTE -->
					<xsl:for-each select="attr">
						<attribute_filter>
							<xsl:for-each select="attribute_filter">
								<attribute_filters>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:for-each select="elem">
												<filter_col>
													<attribute>
														<xsl:value-of select="@id"/>
													</attribute>
													<xsl:for-each select="elem">
														<col_entry>
															<xsl:value-of select="@value"/>
														</col_entry>
													</xsl:for-each>
												</filter_col>
											</xsl:for-each>
										</value>
									</xsl:for-each>
								</attribute_filters>
							</xsl:for-each>
						</attribute_filter>
					</xsl:for-each>

					<!-- DATA -->
					<xsl:for-each select="data">
						<data_filter>
							<xsl:for-each select="subcube">
								<subcube>
									<xsl:for-each select="source_cube">
										<source_cube>
											<xsl:for-each select="param">
												<parameter>
													<xsl:value-of select="@value"/>
												</parameter>
											</xsl:for-each>
											<xsl:for-each select="value">
												<value>
													<xsl:value-of select="@value"/>
												</value>
											</xsl:for-each>
										</source_cube>
									</xsl:for-each>
									<xsl:for-each select="subcube">
										<xsl:for-each select="elem">
											<dimension_coordinates>
												<xsl:for-each select="param">
													<parameter>
														<xsl:value-of select="@value"/>
													</parameter>
												</xsl:for-each>
												<xsl:for-each select="value">
													<value>
														<xsl:if test="@value">
															<element>
																<xsl:value-of select="@value"/>
															</element>
														</xsl:if>
														<xsl:for-each select="elem">
															<element>
																<xsl:value-of select="@value"/>
															</element>
														</xsl:for-each>
													</value>
												</xsl:for-each>
											</dimension_coordinates>
										</xsl:for-each>
									</xsl:for-each>
								</subcube>
							</xsl:for-each>
							<xsl:for-each select="cell_operator">
								<cell_operator>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</cell_operator>
							</xsl:for-each>

							<criteria>
								<xsl:for-each select="criteria">
									<xsl:if test="elem[1]/@value">
										<par1>
											<xsl:if test="elem[2]/param/@value">
												<parameter>
													<xsl:value-of select="elem[2]/param/@value"/>
												</parameter>
											</xsl:if>
											<value>
												<xsl:value-of select="elem[2]/value/@value"/>
											</value>
										</par1>
										<op1>
											<xsl:value-of select="elem[1]/@value"/>
										</op1>
									</xsl:if>
									<xsl:if test="elem[3]/@value">
										<par2>
											<xsl:if test="elem[4]/param/@value">
												<parameter>
													<xsl:value-of select="elem[4]/param/@value"/>
												</parameter>
											</xsl:if>
											<value>
												<xsl:value-of select="elem[4]/value/@value"/>
											</value>
										</par2>
										<op2>
											<xsl:value-of select="elem[3]/@value"/>
										</op2>
									</xsl:if>
								</xsl:for-each>
							</criteria>
							<xsl:for-each select="top">
								<top>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</top>
							</xsl:for-each>
							<xsl:for-each select="upper_percentage">
								<upper_percentage>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</upper_percentage>
							</xsl:for-each>
							<xsl:for-each select="lower_percentage">
								<lower_percentage>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</lower_percentage>
							</xsl:for-each>
						</data_filter>
					</xsl:for-each>

					<!-- SORT -->
					<xsl:for-each select="sort">
						<sorting_filter>
							<xsl:for-each select="whole">
								<whole>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</whole>
							</xsl:for-each>
							<xsl:for-each select="sorting_criteria">
								<sorting_criteria>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</sorting_criteria>
							</xsl:for-each>
							<xsl:for-each select="attribute">
								<attribute>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</attribute>
							</xsl:for-each>
							<xsl:for-each select="type_limitation">
								<type_limitation>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</type_limitation>
							</xsl:for-each>
							<xsl:for-each select="level">
								<level>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</level>
							</xsl:for-each>
							<xsl:for-each select="reverse">
								<reverse>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</reverse>
							</xsl:for-each>
							<xsl:for-each select="show_duplicates">
								<show_duplicates>
									<xsl:for-each select="param">
										<parameter>
											<xsl:value-of select="@value"/>
										</parameter>
									</xsl:for-each>
									<xsl:for-each select="value">
										<value>
											<xsl:value-of select="@value"/>
										</value>
									</xsl:for-each>
								</show_duplicates>
							</xsl:for-each>
						</sorting_filter>
					</xsl:for-each>
				</subset>
			</xsl:for-each>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>
