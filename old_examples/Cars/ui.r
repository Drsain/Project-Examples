load("AudiA4data.Rdata")
shinyUI(pageWithSidebar(
  headerPanel('Buying a used car'),
  sidebarPanel(
    selectInput('xcol', 'X Variable', names(AudiA4data)),
    selectInput('ycol', 'Y Variable', names(AudiA4data),
                selected=names(AudiA4data)[[2]]),
    actionButton("calc", "Caculate best deal")
  ),
  mainPanel(
    plotOutput('plot1')
  )
))